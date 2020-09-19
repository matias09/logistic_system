#ifndef LGLIB_GLOBAL_H
#define LGLIB_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(LGLIB_LIBRARY)
#  define LGLIBSHARED_EXPORT Q_DECL_EXPORT
#else
#  define LGLIBSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // LGLIB_GLOBAL_H
