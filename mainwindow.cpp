#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QRegularExpression>
#include <QStandardPaths>
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    this->setFixedSize(QSize(823,661));
    ui->setupUi(this);
    table = new HashTable(10);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete table;
}

void MainWindow::on_inputFileButton_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Open Input File", "", "Text Files (*.txt);;All Files (*)");
    if (!filePath.isEmpty()) {
        table->inputFile(filePath.toStdString());
        QMessageBox::information(this, "Success", "File loaded successfully!");
        addDebugMessage("Elements were inputted from " + filePath + ".");
        updateElementList();
    }

    on_printTableButton_clicked();
}

void MainWindow::on_printTableButton_clicked()
{
    // Печать в app
    std::ostringstream oss;
    table->print(oss);
    ui->tableOutput->setPlainText(QString::fromStdString(oss.str()));
    addDebugMessage("Table was printed.");

    // Печать в консоль
    table->print();
}

void MainWindow::on_printTreeButton_clicked()
{
    QString data = ui->indexLineEdit->text();

    if (data.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please fill in the field.");
        return;
    }

    bool ok;
    int index = data.toInt(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Warning", "Please enter a valid natural index from table.");
        return;
    }

    if (index > static_cast<int>(table->getKeys().size()) || index < 1) {
        QMessageBox::warning(this, "Warning", "Enter a valid index in range of table size.");
        return;
    }

    // Печать в app
    std::ostringstream oss;
    table->printTree(oss, index - 1);
    ui->treeOutput->setPlainText(QString::fromStdString(oss.str()));
    addDebugMessage("Tree in " + data + " cell of table was printed.");

    // Печать в консоль
    table->printTree(index - 1);
}

void MainWindow::on_addElementButton_clicked()
{
    QString data = ui->dataLineEdit->text();

    if (data.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please fill in the field.");
        return;
    }

    QStringList parts = data.split(' ');
    if (parts.size() < 5) {
        QMessageBox::warning(this, "Warning", "Please enter all required data in the correct format.");
        return;
    }

    QString supplier = parts[0] + " " + parts[1]; // Имя поставщика (первые два слова)
    QString articul = parts[2]; // Артикул на третьем месте
    QString date = parts[3]; // Дата на четвертом месте
    QString product = parts[4]; // Имя продукта на пятом месте
    for (int i = 5; i < parts.size(); ++i) {
        product += " " + parts[i]; // Остальные части относятся к имени продукта
    }

    QRegularExpression dateRegex(R"(\d{2}\.\d{2}\.\d{4})");
    if (!dateRegex.match(date).hasMatch()) {
        QMessageBox::warning(this, "Warning", "Please enter a date in format: dd.mm.yyyy.");
        return;
    }

    // Проверка корректности данных
    if (!table->validateData(supplier.toStdString(), articul.toStdString(), product.toStdString())) {
        QMessageBox::warning(this, "Warning", "Invalid input data.");
        return;
    }


    Date dateObj;
    dateObj.fromString(date.toStdString());

    Element newElement(articul.toStdString(), supplier.toStdString(), product.toStdString(), dateObj);
    if (table->insert(newElement)) {
       QMessageBox::information(this, "Success", "Element added successfully!");
       addDebugMessage("Element was inserted in the table by hand.");
    } else {
       QMessageBox::warning(this, "Warning", "Element already exists.");
       addDebugMessage("Element already exists.");
       return;
    }

    on_printTableButton_clicked();
    updateElementList();
}

void MainWindow::on_removeElementButton_clicked()
{
    QString data = ui->dataLineEdit->text();

    if (data.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please fill in the field.");
        return;
    }

    QStringList parts = data.split(' ');
    if (parts.size() < 5) {
        QMessageBox::warning(this, "Warning", "Please enter all required data in the correct format.");
        return;
    }

    QString supplier = parts[0] + " " + parts[1]; // Имя поставщика (первые два слова)
    QString articul = parts[2]; // Артикул на третьем месте
    QString date = parts[3]; // Дата на четвертом месте
    QString product = parts[4]; // Имя продукта на пятом месте
    for (int i = 5; i < parts.size(); ++i) {
        product += " " + parts[i]; // Остальные части относятся к имени продукта
    }

    QRegularExpression dateRegex(R"(\d{2}\.\d{2}\.\d{4})");
    if (!dateRegex.match(date).hasMatch()) {
        QMessageBox::warning(this, "Warning", "Please enter a date in format dd.mm.yyyy.");
        return;
    }

    // Проверка корректности данных
    if (!table->validateData(supplier.toStdString(), articul.toStdString(), product.toStdString())) {
        QMessageBox::warning(this, "Warning", "Invalid input data.");
        return;
    }

    Date dateObj;
    dateObj.fromString(date.toStdString());

    Element elementToRemove(articul.toStdString(), supplier.toStdString(), product.toStdString(), dateObj);
    if (table->remove(elementToRemove)) {
            QMessageBox::information(this, "Success", "Element removed successfully!");
            addDebugMessage("Element was removed from the table by hand.");
            on_printTableButton_clicked();
            updateElementList();
        } else {
            QMessageBox::warning(this, "Warning", "Element not removed.");
            addDebugMessage("Failed to remove element from the table.");
        }
}

void MainWindow::on_exportToFileButton_clicked()
{
    QString desktopPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    QString filePath = desktopPath + "/output.txt";

    std::ofstream outFile(filePath.toStdString());
    if (!outFile) {
        QMessageBox::warning(this, "Error", "Unable to open file for writing.");
        return;
    }

    std::ostringstream oss;
    const auto& keys = table->getKeys();

    for (size_t i = 0; i < keys.size(); ++i) {
        const auto& key = keys[i];
        if (key) {
            if (key->getTree() && key->getTree()->getRoot()) {
                printTreeElements(oss, key->getTree()->getRoot());
            }
        }
    }

    outFile << oss.str();
    outFile.close();

    QMessageBox::information(this, "Success", "Table exported to " + filePath + " successfully!");
    addDebugMessage("Table was exported to the file " + filePath);
}


void MainWindow::on_findElementButton_clicked()
{
    QString data = ui->dataLineEdit->text();

    if (data.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please fill in the field.");
        return;
    }

    QStringList parts = data.split(' ');
    if (parts.size() < 5) {
        QMessageBox::warning(this, "Warning", "Please enter data in correct format.");
        return;
    }

    QString supplier = parts[0] + " " + parts[1]; // Имя поставщика (первые два слова)
    QString articul = parts[2]; // Артикул на третьем месте
    QString date = parts[3]; // Дата на четвертом месте
    QString product = parts[4]; // Имя продукта на пятом месте
    for (int i = 5; i < parts.size(); ++i) {
        product += " " + parts[i]; // Остальные части относятся к имени продукта
    }

    QRegularExpression dateRegex(R"(\d{2}\.\d{2}\.\d{4})");
    if (!dateRegex.match(date).hasMatch()) {
        QMessageBox::warning(this, "Warning", "Please enter a valid date in the format dd.mm.yyyy.");
        return;
    }

    // Проверка корректности данных
    if (!table->validateData(supplier.toStdString(), articul.toStdString(), product.toStdString())) {
        QMessageBox::warning(this, "Warning", "Invalid input data.");
        return;
    }

    Date dateObj;
    dateObj.fromString(date.toStdString());

    Element elementToFind(articul.toStdString(), supplier.toStdString(), product.toStdString(), dateObj);
    int found = table->find(elementToFind) + 1;

    if (found == 0) {
        QMessageBox::warning(this, "Warning", "Element not found in the table.");
        cout << "Element not found in the table.\n";
        addDebugMessage("Element not found in the table.");
    } else {
        QMessageBox::information(this, "Success", "Element found in " + QString::number(found) + " cell of the table.");
        cout << "Element found in " << found << " cell of the table.\n";
        addDebugMessage("Element found in " + QString::number(found) + " cell of the table.");
    }

}

void MainWindow::on_exampleInputButton_clicked()
{
    QMessageBox::information(this, "Input Example", "IP Polyakov l4v66hc6d5 10.07.2024 gaming laptop");
    addDebugMessage("Example was printed.");
}

void MainWindow::updateElementList()
{
    std::ostringstream oss;

    const auto& keys = table->getKeys();

    for (size_t i = 0; i < keys.size(); ++i) {
        const auto& key = keys[i];
        if (key) {
            if (key->getTree() && key->getTree()->getRoot()) {
                printTreeElements(oss, key->getTree()->getRoot());
            }
        }
    }

    ui->elementListOutput->setPlainText(QString::fromStdString(oss.str()));
    addDebugMessage("Basic list was updated.");
}

void MainWindow::printTreeElements(std::ostringstream& oss, const Node* node) {
    if (!node) return;

    if (node->_right) {
        printTreeElements(oss, node->_right);
    }

    Element element = node->getElement();
    oss << element.getNameSupplier() << " " << element.getArticul() << " " << element.getDate().toString() << " " << element.getNameProduct() << "\n";

    if (node->_left) {
        printTreeElements(oss, node->_left);
    }
}

void MainWindow::addDebugMessage(const QString& message) {
    ui->debugOutput->append(message);
}

void MainWindow::on_setSizeButton_clicked()
{
    bool ok;
    int size = QInputDialog::getInt(this, tr("Set Hash Table Size"),
                                    tr("Size:"), 10, 1, 10000, 1, &ok);
    if (ok) {
        delete table;
        table = new HashTable(size);
        QMessageBox::information(this, "Success", "Hash table size set to " + QString::number(size));
    }
}

void MainWindow::on_clearButton_clicked()
{
    delete table;
    table = new HashTable(10);
    QMessageBox::information(this, "Success", "Hash table cleared.");
    addDebugMessage("Hash table was cleared.");
    updateElementList();
    on_printTableButton_clicked();
}
