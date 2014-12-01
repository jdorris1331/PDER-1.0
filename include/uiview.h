#ifndef UIVIEW_H
#define UIVIEW_H

#include <QMainWindow>

namespace Ui {
class UIView;
}

class UIView : public QMainWindow
{
    Q_OBJECT

public:
    explicit UIView(QWidget *parent = 0);
    ~UIView();

private slots:
    void on_slideOmega_sliderMoved(int position);

private:
    Ui::UIView *ui;
};

#endif // UIVIEW_H
