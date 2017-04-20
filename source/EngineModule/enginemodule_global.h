#ifndef ENGINEMODULE_GLOBAL_H
#define ENGINEMODULE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(ENGINEMODULE_LIBRARY)
#  define ENGINEMODULESHARED_EXPORT Q_DECL_EXPORT
#else
#  define ENGINEMODULESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // ENGINEMODULE_GLOBAL_H
