#include <QDialog>
#include <QFileSystemModel>
#include <qlistview.h>
#include <QUrl>
#include <QLineEdit>
#include <QKeyEvent>
#include <vector>
#include <utility>

class FSView : public QDialog
{

    Q_OBJECT

    QFileSystemModel mModel;
    QListView mList;
    QLineEdit mEnterField;
    QString mSearchText{};
    bool mSearchMode{false};
    std::vector<std::pair<QUrl, int>> mMatching;
    std::vector<std::pair<QUrl, int>>::iterator mCurrent{mMatching.end()};

public:
    FSView();

protected:
    virtual void keyPressEvent (QKeyEvent * event);

private:
    void focusNextMatching();
    void clearMatching(const QString& string);

    //matching works in additive maner
    void narrowMatching(const QString& string);
    void broadMatching(const QString& string);

private slots:
    void createMatching(const QString& string);
    void modelDirectoryLoaded(const QString& string);

signals:
    void DirectoryActivated(const QUrl& url);
    void DirectoryEntered(const QUrl& url);
};
