#ifndef CHECKERMODELE_H
#define CHECKERMODELE_H

#include <QWidget>
#include <QDialog>

#include "AbstractChecker.h"
#include "GlobalChecker.h"


namespace Ui {
class CheckerModele;
}
/**
 * @brief The CheckerModele class provide a basic QDialog interface for AbstractChecker. CheckerModele's ui display some pushButton and an AbstractChecker as content QWidget. CheckerModele is an overlay for AbstractChecker.
 *
 */
class CheckerModele : public QDialog
{
    Q_OBJECT
public:
    /**
     * @brief CheckerModele Constructs a checkerModele overlay for AbstractChecker with a parent
     * @param parent
     */
    explicit CheckerModele(QWidget *parent = 0);
    ~CheckerModele();
public slots:
    /**
     * @brief setContentWidget Set a QWidget to display as contentWidget. The must is an AbstractChecker QWidget.
     * @param content the QWidget pointer to display through the CheckerModele.
     */
    void setContentWidget( QWidget* content );

private slots:
    /**
     * @brief on_close_clicked Called when the user click on the Close Button. execute the reject() method inherited from QDialog.
     */
    void on_close_clicked();
    /**
     * @brief on_help_clicked Called when the user click on the Help Button. Return a code value with hte done() method inherited from QDialog.
     */
    void on_help_clicked();
    /**
     * @brief on_pushButton_clicked Call the updateModuleValues() method from the current contentWidget.
     */
    void on_pushButton_clicked();

private:
    /**
     * @brief ui Graphical layer
     */
    Ui::CheckerModele *ui;
};

#endif // CHECKERMODELE_H

