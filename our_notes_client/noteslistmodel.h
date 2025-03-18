#ifndef NOTESLISTMODEL_H
#define NOTESLISTMODEL_H

#include <QAbstractListModel>

struct NoteData {
    int id;
    QString NameNote;
    QString contentNote;
    QString usersАccess;
};

class NotesListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum NotesRoles{
        IdNoteRole = Qt::UserRole + 1,
        NameNoteRole,
        ContentNoteRole,
        UsersAccessRole
    };

    static NotesListModel *instance();

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    void addNote(const NoteData &note);
    void removeNote(int id);
    void updateNote(int id, const QString &name, const QString &content);

private:
    explicit NotesListModel(QObject *parent = nullptr);
    static NotesListModel* m_instance;

    QList<NoteData> m_notes;
    int findIndexById(int id) const;
};

#endif // NOTESLISTMODEL_H
