/****************************************************************************
** Meta object code from reading C++ file 'glwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.13)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../include/glwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'glwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.13. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_GLWidget_t {
    QByteArrayData data[25];
    char stringdata0[237];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GLWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GLWidget_t qt_meta_stringdata_GLWidget = {
    {
QT_MOC_LITERAL(0, 0, 8), // "GLWidget"
QT_MOC_LITERAL(1, 9, 9), // "addObject"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 17), // "addObjectFromFile"
QT_MOC_LITERAL(4, 38, 8), // "filename"
QT_MOC_LITERAL(5, 47, 10), // "clearScene"
QT_MOC_LITERAL(6, 58, 11), // "resetCamera"
QT_MOC_LITERAL(7, 70, 8), // "drawAxes"
QT_MOC_LITERAL(8, 79, 9), // "drawPoint"
QT_MOC_LITERAL(9, 89, 6), // "Vector"
QT_MOC_LITERAL(10, 96, 3), // "pos"
QT_MOC_LITERAL(11, 100, 1), // "r"
QT_MOC_LITERAL(12, 102, 1), // "g"
QT_MOC_LITERAL(13, 104, 1), // "b"
QT_MOC_LITERAL(14, 106, 24), // "boundingBoxIncludingAxes"
QT_MOC_LITERAL(15, 131, 3), // "Box"
QT_MOC_LITERAL(16, 135, 10), // "loadPlugin"
QT_MOC_LITERAL(17, 146, 11), // "loadPlugins"
QT_MOC_LITERAL(18, 158, 4), // "list"
QT_MOC_LITERAL(19, 163, 18), // "loadDefaultPlugins"
QT_MOC_LITERAL(20, 182, 8), // "QString&"
QT_MOC_LITERAL(21, 191, 7), // "plugins"
QT_MOC_LITERAL(22, 199, 22), // "resetPluginsToDefaults"
QT_MOC_LITERAL(23, 222, 12), // "unloadPlugin"
QT_MOC_LITERAL(24, 235, 1) // "i"

    },
    "GLWidget\0addObject\0\0addObjectFromFile\0"
    "filename\0clearScene\0resetCamera\0"
    "drawAxes\0drawPoint\0Vector\0pos\0r\0g\0b\0"
    "boundingBoxIncludingAxes\0Box\0loadPlugin\0"
    "loadPlugins\0list\0loadDefaultPlugins\0"
    "QString&\0plugins\0resetPluginsToDefaults\0"
    "unloadPlugin\0i"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GLWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x0a /* Public */,
       3,    1,   75,    2, 0x0a /* Public */,
       5,    0,   78,    2, 0x0a /* Public */,
       6,    0,   79,    2, 0x0a /* Public */,
       7,    0,   80,    2, 0x0a /* Public */,
       8,    4,   81,    2, 0x0a /* Public */,
      14,    0,   90,    2, 0x0a /* Public */,
      16,    0,   91,    2, 0x0a /* Public */,
      17,    1,   92,    2, 0x0a /* Public */,
      19,    1,   95,    2, 0x0a /* Public */,
      22,    0,   98,    2, 0x0a /* Public */,
      23,    1,   99,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9, QMetaType::Float, QMetaType::Float, QMetaType::Float,   10,   11,   12,   13,
    0x80000000 | 15,
    QMetaType::Void,
    QMetaType::Int, QMetaType::QStringList,   18,
    QMetaType::Void, 0x80000000 | 20,   21,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   24,

       0        // eod
};

void GLWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<GLWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->addObject(); break;
        case 1: _t->addObjectFromFile((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->clearScene(); break;
        case 3: _t->resetCamera(); break;
        case 4: _t->drawAxes(); break;
        case 5: _t->drawPoint((*reinterpret_cast< const Vector(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3])),(*reinterpret_cast< float(*)>(_a[4]))); break;
        case 6: { Box _r = _t->boundingBoxIncludingAxes();
            if (_a[0]) *reinterpret_cast< Box*>(_a[0]) = std::move(_r); }  break;
        case 7: _t->loadPlugin(); break;
        case 8: { int _r = _t->loadPlugins((*reinterpret_cast< const QStringList(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 9: _t->loadDefaultPlugins((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: _t->resetPluginsToDefaults(); break;
        case 11: _t->unloadPlugin((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject GLWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QOpenGLWidget::staticMetaObject>(),
    qt_meta_stringdata_GLWidget.data,
    qt_meta_data_GLWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *GLWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GLWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GLWidget.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "QOpenGLFunctions_3_3_Core"))
        return static_cast< QOpenGLFunctions_3_3_Core*>(this);
    return QOpenGLWidget::qt_metacast(_clname);
}

int GLWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QOpenGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
