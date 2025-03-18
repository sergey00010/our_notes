#include "noteslistmodel.h"

NotesListModel *NotesListModel::m_instance = nullptr;
NotesListModel *NotesListModel::instance() {
    if (!m_instance)
        m_instance = new NotesListModel();
    return m_instance;
}

NotesListModel::NotesListModel(QObject *parent)
    : QAbstractListModel(parent)
{}

int NotesListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_notes.size();
}

QVariant NotesListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_notes.size())
        return QVariant();

    const NoteData &note = m_notes.at(index.row());

    switch (role) {
    case IdNoteRole:
        return note.id;
    case NameNoteRole:
        return note.NameNote;
    case ContentNoteRole:
        return note.contentNote;
    case UsersAccessRole:
        return note.usersАccess;
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> NotesListModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[IdNoteRole] = "id";
    roles[NameNoteRole] = "nameNote";
    roles[ContentNoteRole] = "contentNote";
    roles[UsersAccessRole] = "usersАccess";
    return roles;
}

void NotesListModel::addNote(const NoteData &note) {
    beginInsertRows(QModelIndex(), m_notes.size(), m_notes.size());
    m_notes.append(note);
    endInsertRows();
}

void NotesListModel::removeNote(int id) {
    int index = findIndexById(id);
    if (index == -1)
        return;

    beginRemoveRows(QModelIndex(), index, index);
    m_notes.removeAt(index);
    endRemoveRows();
}

void NotesListModel::updateNote(int id, const QString &name, const QString &content) {
    int index = findIndexById(id);
    if (index == -1)
        return;

    m_notes[index].NameNote = name;
    m_notes[index].contentNote = content;

    QModelIndex modelIndex = createIndex(index, 0);
    emit dataChanged(modelIndex, modelIndex, {NameNoteRole, ContentNoteRole, UsersAccessRole});
}

int NotesListModel::findIndexById(int id) const {
    for (int i = 0; i < m_notes.size(); ++i) {
        if (m_notes.at(i).id == id) {
            return i;
        }
    }
    return -1;
}

