#ifndef T_PAGE1_H
#define T_PAGE1_H

#include "ElaScrollPage.h"

class T_Page1 : public ElaScrollPage
{
    Q_OBJECT
public:
    explicit T_Page1(QWidget* parent = nullptr);
    ~T_Page1() override;
};

#endif // T_PAGE1_H
