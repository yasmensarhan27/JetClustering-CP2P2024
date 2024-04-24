#ifndef ROOT_RConfigOptions
#define ROOT_RConfigOptions

#define R__CONFIGUREOPTIONS   "BLAS_flexiblas_LIBRARY=/usr/lib64/libflexiblas.so CFITSIO_INCLUDE_DIR=/usr/include/cfitsio CFITSIO_LIBRARY=/usr/lib64/libcfitsio.so DAVIX_INCLUDEDIR=/usr/include DAVIX_INCLUDE_DIR=/usr/include/davix DAVIX_INCLUDE_DIRS=/usr/include/davix DAVIX_LIBRARIES=-ldavix DAVIX_LIBRARY=-ldavix DAVIX_STATIC_INCLUDE_DIRS=/usr/include/davix DAVIX_STATIC_LIBRARIES=davix DAVIX_VERSION=0.8.5 FREETYPE_INCLUDE_DIR_freetype2=/usr/include/freetype2 FREETYPE_INCLUDE_DIR_ft2build=/usr/include/freetype2 FREETYPE_LIBRARY_RELEASE=/usr/lib64/libfreetype.so FTGL_INCLUDE_DIR=/usr/include FTGL_LIBRARY=/lib64/libftgl.so Fontconfig_INCLUDE_DIR=/usr/include Fontconfig_LIBRARY=/usr/lib64/libfontconfig.so GIF_INCLUDE_DIR=/usr/include GIF_LIBRARY=/usr/lib64/libgif.so GL2PS_INCLUDE_DIR=/usr/include GL2PS_LIBRARY=/lib64/libgl2ps.so GLEW_INCLUDE_DIR=/usr/include GLEW_SHARED_LIBRARY_RELEASE=/usr/lib64/libGLEW.so GMOCK_INCLUDE_DIRS=/usr/include GMOCK_LIBRARIES=/usr/lib64/libgmock.so GMOCK_MAIN_LIBRARIES=/usr/lib64/libgmock_main.so GTEST_INCLUDE_DIRS=/usr/include GTEST_LIBRARIES=/usr/lib64/libgtest.so GTEST_MAIN_LIBRARIES=/usr/lib64/libgtest_main.so JPEG_INCLUDE_DIR=/usr/include JPEG_LIBRARY=/usr/lib64/libjpeg.so JPEG_LIBRARY_RELEASE=/usr/lib64/libjpeg.so LIBLZMA_INCLUDE_DIR=/usr/include LIBLZMA_LIBRARY=/usr/lib64/liblzma.so LIBLZMA_LIBRARY_RELEASE=/usr/lib64/liblzma.so LIBXML2_INCLUDE_DIR=/usr/include/libxml2 LIBXML2_LIBRARY=/usr/lib64/libxml2.so LZ4_INCLUDE_DIR=/usr/include LZ4_LIBRARY=/usr/lib64/liblz4.so MYSQL_INCLUDE_DIR=/usr/include/mysql NUMPY_INCLUDE_DIRS=/py-venv/ROOT-CI/lib64/python3.9/site-packages/numpy/core/include OPENGL_EGL_INCLUDE_DIR=/usr/include OPENGL_GLX_INCLUDE_DIR=/usr/include OPENGL_INCLUDE_DIR=/usr/include OPENGL_egl_LIBRARY=/usr/lib64/libEGL.so OPENGL_glu_LIBRARY=/usr/lib64/libGLU.so OPENGL_glx_LIBRARY=/usr/lib64/libGLX.so OPENGL_opengl_LIBRARY=/usr/lib64/libOpenGL.so OPENSSL_CRYPTO_LIBRARY=/usr/lib64/libcrypto.so OPENSSL_INCLUDE_DIR=/usr/include OPENSSL_SSL_LIBRARY=/usr/lib64/libssl.so PCRE_INCLUDE_DIR=/usr/include PCRE_PCRE_LIBRARY_DEBUG=/usr/lib64/libpcre.so PCRE_PCRE_LIBRARY_RELEASE=/usr/lib64/libpcre.so PC_LIBXML_INCLUDEDIR=/usr/include PC_LIBXML_INCLUDE_DIRS=/usr/include/libxml2 PC_LIBXML_LIBRARIES=xml2 PC_LIBXML_STATIC_INCLUDE_DIRS=/usr/include/libxml2 PC_LIBXML_VERSION=2.9.13 PC_SQLITE_INCLUDEDIR=/usr/include PC_SQLITE_LIBRARIES=sqlite3 PC_SQLITE_VERSION=3.34.1 PKG_FONTCONFIG_INCLUDEDIR=/usr/include PKG_FONTCONFIG_VERSION=2.14.0 PNG_LIBRARY_RELEASE=/usr/lib64/libpng.so PNG_PNG_INCLUDE_DIR=/usr/include PYTHON_INCLUDE_DIRS=/usr/include/python3.9 PYTHON_LIBRARIES=/usr/lib64/libpython3.9.so PYTHON_LIBRARY_DIR=/usr/lib64 PYTHON_VERSION_MAJOR=3 PYTHON_VERSION_MINOR=9 PYTHON_VERSION_STRING=3.9.18 PostgreSQL_INCLUDE_DIR=/usr/include PostgreSQL_LIBRARY=/usr/lib64/libpq.so Protobuf_INCLUDE_DIR=/usr/include Protobuf_LIBRARY_DEBUG=/usr/lib64/libprotobuf.so Protobuf_LIBRARY_RELEASE=/usr/lib64/libprotobuf.so Protobuf_PROTOC_LIBRARY_DEBUG=/usr/lib64/libprotoc.so Protobuf_PROTOC_LIBRARY_RELEASE=/usr/lib64/libprotoc.so SQLITE_INCLUDE_DIR=/usr/include SQLITE_LIBRARIES=/usr/lib64/libsqlite3.so TBB_INCLUDE_DIR=/usr/include TBB_LIBRARY=/usr/lib64/libtbb.so TBB_LIBRARY_RELEASE=/usr/lib64/libtbb.so TIFF_INCLUDE_DIR=/usr/include TIFF_LIBRARY_RELEASE=/usr/lib64/libtiff.so UUID_INCLUDE_DIR=/usr/include UUID_LIBRARY=uuid X11_X11_INCLUDE_PATH=/usr/include X11_X11_xcb_INCLUDE_PATH=/usr/include X11_XShm_INCLUDE_PATH=/usr/include X11_XSync_INCLUDE_PATH=/usr/include X11_Xaccessstr_INCLUDE_PATH=/usr/include X11_Xau_INCLUDE_PATH=/usr/include X11_Xext_INCLUDE_PATH=/usr/include X11_Xft_INCLUDE_PATH=/usr/include X11_Xkb_INCLUDE_PATH=/usr/include X11_Xkblib_INCLUDE_PATH=/usr/include X11_Xlib_INCLUDE_PATH=/usr/include X11_Xpm_INCLUDE_PATH=/usr/include X11_Xrender_INCLUDE_PATH=/usr/include X11_Xshape_INCLUDE_PATH=/usr/include X11_Xutil_INCLUDE_PATH=/usr/include X11_dpms_INCLUDE_PATH=/usr/include X11_xcb_INCLUDE_PATH=/usr/include X11_xcb_xfixes_INCLUDE_PATH=/usr/include XROOTD_INCLUDE_DIR=/usr/include/xrootd XROOTD_XrdCl_LIBRARY=/usr/lib64/libXrdCl.so XROOTD_XrdUtils_LIBRARY=/usr/lib64/libXrdUtils.so ZLIB_INCLUDE_DIR=/usr/include ZLIB_LIBRARY_RELEASE=/usr/lib64/libz.so ZSTD_INCLUDE_DIR=/usr/include ZSTD_LIBRARIES=/usr/lib64/libzstd.so xxHash_INCLUDE_DIR=/usr/include xxHash_LIBRARY=/usr/lib64/libxxhash.so "
#define R__CONFIGUREFEATURES  "cxx17  asimage builtin_afterimage builtin_clang builtin_cling builtin_llvm builtin_nlohmannjson builtin_openui5 builtin_vdt clad dataframe test_distrdf_pyspark test_distrdf_dask davix fitsio gdml http imt mlp minuit2 mysql opengl pgsql proof pyroot roofit webgui root7 rpath runtime_cxxmodules shared sqlite ssl tmva tmva-cpu tmva-sofie tmva-pymva spectrum unfold vdt x11 xml xrootd"

#endif
