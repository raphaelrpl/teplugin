#ifndef _TERRALIB_<%= appname %>_H_
#define _TERRALIB_<%= appname %>_H_

#include <QDialog>

class Dialog: public QDialog
{
  Q_OBJECT

  public:
    Dialog();
    ~Dialog();
};

#endif //_TERRALIB_<%= appname %>_H_