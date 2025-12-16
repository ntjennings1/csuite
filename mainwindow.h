#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QPlainTextEdit>
#include <QComboBox>

namespace Ui{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

        std::string getDirection();
        void setDirection(std::string direction);
        std::string getCipher();
        void setCipher(std::string cipher);
        std::string getPtext();
        void setPtext(std::string ptext);
        std::string getCtext();
        void setCtext(std::string ctext);
        std::string getKey();
        void setKey(std::string key);

        void throw_exec(std::string type);
        void reset();
        void config(std::string type);
        void clear_entries(std::string type);

    private:
        Ui::MainWindow *ui;

        std::string direction = "f";
        std::string cipher = "";
        std::string ptext = "";
        std::string ctext = "";
        std::string key = "";
        std::string logf = "";

    private slots:

        void onStartbuttonClicked();
        void onResetbuttonClicked();
        void onReversebuttonClicked();
        void onClosebuttonClicked();

        void onComboboxSelection();
        void onFocusChanged();

};

#endif // MAINWINDOW_H
