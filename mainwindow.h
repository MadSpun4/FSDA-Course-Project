#ifndef MAIN_H
#define MAIN_H

#include <QMainWindow>
#include "HashTable/HashTable.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_inputFileButton_clicked();
    void on_printTableButton_clicked();
    void on_printTreeButton_clicked();
    void on_addElementButton_clicked();
    void on_removeElementButton_clicked();
    void on_exportToFileButton_clicked();
    void on_findElementButton_clicked();
    void on_exampleInputButton_clicked();
    void updateElementList();
    void on_setSizeButton_clicked();
    void on_clearButton_clicked();

private:
    Ui::MainWindow *ui;
    HashTable *table;

    void printTreeElements(std::ostringstream& oss, const Node* node);
    void addDebugMessage(const QString& message);
};

#endif // MAIN_H
