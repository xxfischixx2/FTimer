#ifndef FTIMER_GLOBAL_H
#define FTIMER_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(FTIMER_LIBRARY)
#  define FTIMERSHARED_EXPORT Q_DECL_EXPORT
#else
#  define FTIMERSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // FTIMER_GLOBAL_H
