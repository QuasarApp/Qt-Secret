#ifndef QTSECRET_GLOBAL_H
#define QTSECRET_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(Qt_SECRET_LIBRARY)
#  define Qt_SECRETSHARED_EXPORT Q_DECL_EXPORT
#else
#  define Qt_SECRETSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // QTSECRET_GLOBAL_H
