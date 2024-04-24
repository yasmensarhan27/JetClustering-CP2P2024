/// \file ROOT/RNTuplerInspector.hxx
/// \ingroup NTuple ROOT7
/// \author Florine de Geus <florine.de.geus@cern.ch>
/// \date 2023-01-09
/// \warning This is part of the ROOT 7 prototype! It will change without notice. It might trigger earthquakes. Feedback
/// is welcome!

/*************************************************************************
 * Copyright (C) 1995-2023, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

#ifndef ROOT7_RNTupleInspector
#define ROOT7_RNTupleInspector

#include <ROOT/RError.hxx>
#include <ROOT/RNTuple.hxx>
#include <ROOT/RNTupleDescriptor.hxx>

#include <TFile.h>
#include <TH1D.h>

#include <cstdlib>
#include <memory>
#include <regex>
#include <vector>

namespace ROOT {
namespace Experimental {

enum class ENTupleInspectorPrintFormat { kTable, kCSV };
enum class ENTupleInspectorHist { kCount, kNElems, kCompressedSize, kUncompressedSize };

// clang-format off
/**
\class ROOT::Experimental::RNTupleInspector
\ingroup NTuple
\brief Inspect on-disk and storage-related information of an RNTuple.

The RNTupleInspector can be used for studying an RNTuple in terms of its storage efficiency. It provides information on
the level of the RNTuple itself, on the (sub)field level and on the column level.

Example usage:

~~~ {.cpp}
#include <ROOT/RNTuple.hxx>
#include <ROOT/RNTupleInspector.hxx>

#include <iostream>

using ROOT::Experimental::RNTuple;
using ROOT::Experimental::RNTupleInspector;

auto file = TFile::Open("data.rntuple");
auto rntuple = file->Get<RNTuple>("NTupleName");
auto inspector = RNTupleInspector::Create(rntuple).Unwrap();

std::cout << "The compression factor is " << inspector->GetCompressionFactor()
          << " using compression settings " << inspector->GetCompressionSettings()
          << std::endl;
~~~
*/
// clang-format on
class RNTupleInspector {
public:
   /////////////////////////////////////////////////////////////////////////////
   /// \brief Holds column-level storage information.
   ///
   /// The RColumnInfo class provides storage information for an individual column. This information is either
   /// collected during the construction of the RNTupleInpector object, or can be accessed using
   /// the RColumnDescriptor that belongs to this column.
   class RColumnInfo {
   private:
      const RColumnDescriptor &fColumnDescriptor;
      std::uint64_t fCompressedSize = 0;
      std::uint32_t fElementSize = 0;
      std::uint64_t fNElements = 0;

   public:
      RColumnInfo(const RColumnDescriptor &colDesc, std::uint64_t onDiskSize, std::uint32_t elemSize,
                  std::uint64_t nElems)
         : fColumnDescriptor(colDesc), fCompressedSize(onDiskSize), fElementSize(elemSize), fNElements(nElems){};
      ~RColumnInfo() = default;

      const RColumnDescriptor &GetDescriptor() const { return fColumnDescriptor; }
      std::uint64_t GetCompressedSize() const { return fCompressedSize; }
      std::uint64_t GetUncompressedSize() const { return fElementSize * fNElements; }
      std::uint64_t GetElementSize() const { return fElementSize; }
      std::uint64_t GetNElements() const { return fNElements; }
      EColumnType GetType() const { return fColumnDescriptor.GetModel().GetType(); }
   };

   /////////////////////////////////////////////////////////////////////////////
   /// \brief Holds field-level storage information.
   ///
   /// The RFieldTreeInfo class provides storage information for a field **and** its subfields. This information is
   /// either collected during the construction of the RNTupleInpector object, or can be accessed using
   /// the RFieldDescriptor that belongs to this field.
   class RFieldTreeInfo {
   private:
      const RFieldDescriptor &fRootFieldDescriptor;
      std::uint64_t fCompressedSize = 0;
      std::uint64_t fUncompressedSize = 0;

   public:
      RFieldTreeInfo(const RFieldDescriptor &fieldDesc, std::uint64_t onDiskSize, std::uint64_t inMemSize)
         : fRootFieldDescriptor(fieldDesc), fCompressedSize(onDiskSize), fUncompressedSize(inMemSize){};
      ~RFieldTreeInfo() = default;

      const RFieldDescriptor &GetDescriptor() const { return fRootFieldDescriptor; }
      std::uint64_t GetCompressedSize() const { return fCompressedSize; }
      std::uint64_t GetUncompressedSize() const { return fUncompressedSize; }
   };

private:
   std::unique_ptr<TFile> fSourceFile;
   std::unique_ptr<Detail::RPageSource> fPageSource;
   std::unique_ptr<RNTupleDescriptor> fDescriptor;
   int fCompressionSettings = -1;
   std::uint64_t fCompressedSize = 0;
   std::uint64_t fUncompressedSize = 0;

   std::map<int, RColumnInfo> fColumnInfo;
   std::map<int, RFieldTreeInfo> fFieldTreeInfo;

   RNTupleInspector(std::unique_ptr<Detail::RPageSource> pageSource);

   /////////////////////////////////////////////////////////////////////////////
   /// \brief Gather column-level and RNTuple-level information.
   ///
   /// \note This method is called when the RNTupleInspector is initially created. This means that anything unexpected
   /// about the RNTuple itself (e.g. inconsistent compression settings across clusters) will be detected here.
   /// Therefore, any related exceptions will be thrown on creation of the inspector.
   void CollectColumnInfo();

   /////////////////////////////////////////////////////////////////////////////
   /// \brief Recursively gather field-level information.
   ///
   /// \param[in] fieldId The ID of the field from which to start the recursive traversal. Typically this is the "zero
   /// ID", i.e. the logical parent of all top-level fields.
   ///
   /// \return The RFieldTreeInfo for the provided field ID.
   ///
   // / This method iscalled when the RNTupleInpector is initially created.
   RFieldTreeInfo CollectFieldTreeInfo(DescriptorId_t fieldId);

   /////////////////////////////////////////////////////////////////////////////
   /// \brief Get the columns that make up the given field, including its subfields.
   ///
   /// \param [in] fieldId The ID of the field for which to collect the columns.
   ///
   /// \return A vector containing the IDs of all columns for the provided field ID.
   std::vector<DescriptorId_t> GetColumnsByFieldId(DescriptorId_t fieldId) const;

public:
   RNTupleInspector(const RNTupleInspector &other) = delete;
   RNTupleInspector &operator=(const RNTupleInspector &other) = delete;
   RNTupleInspector(RNTupleInspector &&other) = delete;
   RNTupleInspector &operator=(RNTupleInspector &&other) = delete;
   ~RNTupleInspector() = default;

   /////////////////////////////////////////////////////////////////////////////
   /// \brief Create a new RNTupleInspector.
   ///
   /// \param[in] sourceNTuple A pointer to the RNTuple to be inspected.
   ///
   /// \return A pointer to the newly created RNTupleInspector.
   ///
   /// \note When this factory method is called, all required static information is collected from the RNTuple's fields
   /// and underlying columns are collected at ones. This means that when any inconsistencies are encountered (e.g.
   /// inconsistent compression across clusters), it will throw an error here.
   static std::unique_ptr<RNTupleInspector> Create(RNTuple *sourceNTuple);

   /////////////////////////////////////////////////////////////////////////////
   /// \brief Create a new RNTupleInspector.
   ///
   /// \param[in] ntupleName The name of the RNTuple to be inspected.
   /// \param[in] storage The path or URI to the RNTuple to be inspected.
   ///
   /// \see Create(RNTuple *sourceNTuple)
   static std::unique_ptr<RNTupleInspector> Create(std::string_view ntupleName, std::string_view storage);

   /////////////////////////////////////////////////////////////////////////////
   /// \brief Create a new RNTupleInspector.
   ///
   /// \param[in] pageSource The RPageSource object belonging to the RNTuple to be inspected.
   ///
   /// \see Create(RNTuple *sourceNTuple)
   static std::unique_ptr<RNTupleInspector> Create(std::unique_ptr<Detail::RPageSource> pageSource);

   /////////////////////////////////////////////////////////////////////////////
   /// \brief Get the descriptor for the RNTuple being inspected.
   ///
   /// \return A static copy of the RNTupleDescriptor belonging to the inspected RNTuple.
   RNTupleDescriptor *GetDescriptor() const { return fDescriptor.get(); }

   /////////////////////////////////////////////////////////////////////////////
   /// \brief Get the compression settings of the RNTuple being inspected.
   ///
   /// \return The integer representation (\f$algorithm * 10 + level\f$, where \f$algorithm\f$ follows
   /// ROOT::RCompressionSetting::ELevel::EValues) of the compression settings used for the inspected RNTuple.
   ///
   /// \note Here, we assume that the compression settings are consistent across all clusters and columns. If this is
   /// not the case, an exception will be thrown when RNTupleInspector::Create is called.
   int GetCompressionSettings() const { return fCompressionSettings; }

   /////////////////////////////////////////////////////////////////////////////
   /// \brief Get a string describing compression settings of the RNTuple being inspected.
   ///
   /// \return A string describing the compression used for the inspected RNTuple. The format of the string is
   /// `"A (level L)"`, where `A` is the name of the compression algorithm and `L` the compression level.
   ///
   /// \note Here, we assume that the compression settings are consistent across all clusters and columns. If this is
   /// not the case, an exception will be thrown when RNTupleInspector::Create is called.
   std::string GetCompressionSettingsAsString() const;

   /////////////////////////////////////////////////////////////////////////////
   /// \brief Get the compressed, on-disk size of the RNTuple being inspected.
   ///
   /// \return The compressed size of the inspected RNTuple, in bytes, excluding the size of the header and footer.
   std::uint64_t GetCompressedSize() const { return fCompressedSize; }

   /////////////////////////////////////////////////////////////////////////////
   /// \brief Get the uncompressed total size of the RNTuple being inspected.
   ///
   /// \return The uncompressed size of the inspected RNTuple, in bytes, excluding the size of the header and footer.
   std::uint64_t GetUncompressedSize() const { return fUncompressedSize; }

   /////////////////////////////////////////////////////////////////////////////
   /// \brief Get the compression factor of the RNTuple being inspected.
   ///
   /// \return The compression factor of the inspected RNTuple.
   ///
   /// The compression factor shows how well the data present in the RNTuple is compressed by the compression settings
   /// that were used. The compression factor is calculated as \f$size_{uncompressed} / size_{compressed}\f$.
   float GetCompressionFactor() const { return (float)fUncompressedSize / (float)fCompressedSize; }

   /////////////////////////////////////////////////////////////////////////////
   /// \brief Get storage information for a given column.
   ///
   /// \param[in] physicalColumnId The physical ID of the column for which to get the information.
   ///
   /// \return The storage information for the provided column.
   const RColumnInfo &GetColumnInfo(DescriptorId_t physicalColumnId) const;

   /////////////////////////////////////////////////////////////////////////////
   /// \brief Get the number of columns of a given type present in the RNTuple.
   ///
   /// \param[in] colType The column type to count, as defined by ROOT::Experimental::EColumnType.
   ///
   /// \return The number of columns present in the inspected RNTuple of the provided type.
   size_t GetColumnCountByType(EColumnType colType) const;

   /////////////////////////////////////////////////////////////////////////////
   /// \brief Get the IDs of all columns with the given type.
   ///
   /// \param[in] colType The column type to collect, as defined by ROOT::Experimental::EColumnType.
   ///
   /// \return A vector containing the physical IDs of columns of the provided type.
   const std::vector<DescriptorId_t> GetColumnsByType(EColumnType colType);

   /////////////////////////////////////////////////////////////////////////////
   /// \brief Print storage information per column type.
   ///
   /// \param[in] format Whether to print the information as a (markdown-parseable) table or in CSV format.
   /// \param[in] output Where to write the output to. Default is `stdout`.
   ///
   /// The output includes for each column type its count, the total number of elements, the compressed size and the
   /// uncompressed size.
   ///
   /// **Example: printing the column type information of an RNTuple as a table**
   /// ~~~ {.cpp}
   /// #include <ROOT/RNTupleInspector.hxx>
   /// using ROOT::Experimental::RNTupleInspector;
   /// using ROOT::Experimental::ENTupleInspectorPrintFormat;
   ///
   /// auto inspector = RNTupleInspector::Create("myNTuple", "some/file.root");
   /// inspector->PrintColumnTypeInfo();
   /// ~~~
   /// Ouput:
   /// ~~~
   ///  column type    | count   | # elements      | compressed bytes  | uncompressed bytes
   /// ----------------|---------|-----------------|-------------------|--------------------
   ///    SplitIndex64 |       2 |             150 |                72 |               1200
   ///     SplitReal32 |       4 |             300 |               189 |               1200
   ///     SplitUInt32 |       3 |             225 |               123 |                900
   /// ~~~
   ///
   /// **Example: printing the column type information of an RNTuple in CSV format**
   /// ~~~ {.cpp}
   /// #include <ROOT/RNTupleInspector.hxx>
   /// using ROOT::Experimental::RNTupleInspector;
   /// using ROOT::Experimental::ENTupleInspectorPrintFormat;
   ///
   /// auto inspector = RNTupleInspector::Create("myNTuple", "some/file.root");
   /// inspector->PrintColumnTypeInfo();
   /// ~~~
   /// Ouput:
   /// ~~~
   /// columnType,count,nElements,compressedSize,uncompressedSize
   /// SplitIndex64,2,150,72,1200
   /// SplitReal32,4,300,189,1200
   /// SplitUInt32,3,225,123,900
   /// ~~~
   void PrintColumnTypeInfo(ENTupleInspectorPrintFormat format = ENTupleInspectorPrintFormat::kTable,
                            std::ostream &output = std::cout);

   /////////////////////////////////////////////////////////////////////////////
   /// \brief Get a histogram showing information for each column type present,
   ///
   /// \param[in] histKind Which type of information should be returned.
   /// \param[in] histName The name of the histogram. An empty string means a default name will be used.
   /// \param[in] histTitle The title of the histogram. An empty string means a default title will be used.
   ///
   /// \return A pointer to a `TH1D` containing the specified kind of information.
   ///
   /// Get a histogram showing the count, number of elements, size on disk, or size in memory for each column
   /// type present in the inspected RNTuple.
   std::unique_ptr<TH1D> GetColumnTypeInfoAsHist(ENTupleInspectorHist histKind, std::string_view histName = "",
                                                 std::string_view histTitle = "");

   /////////////////////////////////////////////////////////////////////////////
   /// \brief Get storage information for a given (sub)field by ID.
   ///
   /// \param[in] fieldId The ID of the (sub)field for which to get the information.
   ///
   /// \return The storage information for the provided (sub)field.
   const RFieldTreeInfo &GetFieldTreeInfo(DescriptorId_t fieldId) const;

   /////////////////////////////////////////////////////////////////////////////
   /// \brief Get storage information for a given (sub)field by name.
   ///
   /// \param[in] fieldName The name of the (sub)field for which to get the information.
   ///
   /// \return The storage information for the provided (sub)field.
   const RFieldTreeInfo &GetFieldTreeInfo(std::string_view fieldName) const;

   /////////////////////////////////////////////////////////////////////////////
   /// \brief Get the number of fields of a given type or class present in the RNTuple.
   ///
   /// \param[in] typeNamePattern The type or class name to count. May contain regular expression patterns for grouping
   /// multiple kinds of types or classes.
   /// \param[in] searchInSubFields If set to `false`, only top-level fields will be considered.
   ///
   /// \return The number of fields that matches the provided type.
   size_t GetFieldCountByType(const std::regex &typeNamePattern, bool searchInSubFields = true) const;

   /////////////////////////////////////////////////////////////////////////////
   /// \brief Get the number of fields of a given type or class present in the RNTuple.
   ///
   /// \see GetFieldCountByType(const std::regex &typeNamePattern, bool searchInSubFields) const
   size_t GetFieldCountByType(std::string_view typeNamePattern, bool searchInSubFields = true) const
   {
      return GetFieldCountByType(std::regex{std::string(typeNamePattern)}, searchInSubFields);
   }

   /////////////////////////////////////////////////////////////////////////////
   /// \brief Get the IDs of (sub-)fields whose name matches the given string.
   ///
   /// \param[in] fieldNamePattern The name of the field name to get. Because field names are unique by design,
   /// providing a single field name will return a vector containing just the ID of that field. However, regular
   /// expression patterns are supported in order to get the IDs of all fields whose name follow a certain structure.
   /// \param[in] searchInSubFields If set to `false`, only top-level fields will be considered.
   ///
   /// \return A vector containing the IDs of fields that match the provided name.
   const std::vector<DescriptorId_t>
   GetFieldsByName(const std::regex &fieldNamePattern, bool searchInSubFields = true) const;

   /////////////////////////////////////////////////////////////////////////////
   /// \brief Get the IDs of (sub-)fields whose name matches the given string.
   ///
   /// \see GetFieldsByName(const std::regex &fieldNamePattern, bool searchInSubFields) const
   const std::vector<DescriptorId_t> GetFieldsByName(std::string_view fieldNamePattern, bool searchInSubFields = true)
   {
      return GetFieldsByName(std::regex{std::string(fieldNamePattern)}, searchInSubFields);
   }
};
} // namespace Experimental
} // namespace ROOT

#endif // ROOT7_RNTupleInspector