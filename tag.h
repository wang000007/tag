// tag.h
#ifndef TAG_H
#define TAG_H

typedef enum Status {
    ERROR = 0,
    SUCCESS = 1
} Status;

// �ʼǽṹ��
typedef struct note {
    char name[50]; // �ʼ���
    char content[500]; // �ʼ�����
    struct tag* tagHead; // ��ǩ����ͷָ��
    struct note* next; // ��һƪ�ʼǵ�ָ��
} Note;

//�ļ��нṹ��
typedef struct Folder
{
    char name[50];      // �ļ�����
    Tag** tags;          // �洢��ǩ������ͷָ��
    Note* notes;        // ָ��ʼ�����ͷ��ָ��
    int num_notes;// �ʼ�����
} Folder;

// ��ǩ�ṹ��
typedef struct tag {
    char name[20]; // ��ǩ��
    struct tag* next; // ��һ����ǩ��ָ��
} Tag;

// ��ӱ�ǩ���ڲ�����
int addTag(struct tag** tagHead, char* tagName);

// ɾ����ǩ���ڲ�����
int deleteTag(struct tag** tagHead, char* tagName);

// �Ƿ������ǩ���ڲ�����
int isTagContained(struct tag* tagHead, char* tagName);

// ��ӱʼǱ�ǩ
Status addTagToNote(Note* note, char* tagName);

// ɾ���ʼǱ�ǩ
Status deleteTagFromNote(Note* note, char* tagName);

// ��ʾ��ǩ���ڲ�����
void viewTag(struct tag* tagHead);

// ��ʾָ���ʼǵı�ǩ
Status viewTagsInNote(Note* note);

// ����ļ��б�ǩ(ע���ǩ��������⣬�ɹ�����SUCCESS��ʧ�ܷ���ERROR)
Status addTagToFolder(Folder* folder, char* tagName);

// ɾ���ļ��б�ǩ
Status deleteTagFromFolder(Folder* folder, char* tagName);

// ��ʾָ���ļ��еı�ǩ
Status viewTagsInFolder(Folder* folder);
#endif