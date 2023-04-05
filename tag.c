#include "tag.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ��ӱ�ǩ���ڲ�����
int addTag(struct tag** tagHead, char* tagName) {
    if (tagName == NULL || strlen(tagName) == 0) {
        return 0; // ��ǩ��Ϊ�գ����ʧ��
    }
    struct tag* newTag = (struct tag*)malloc(sizeof(struct tag));
    if (newTag == NULL) {
        return 0; // �ڴ����ʧ�ܣ����ʧ��
    }
    strcpy(newTag->name, tagName); // ������ǩ��
    newTag->next = *tagHead; // ���±�ǩ��������ͷ
    *tagHead = newTag;
    return 1; // ��ӳɹ�
}

// ɾ����ǩ���ڲ�����
int deleteTag(struct tag** tagHead, char* tagName) {
    if (*tagHead == NULL || tagName == NULL || strlen(tagName) == 0) {
        return 0; // ����Ϊ�ջ��ǩ��Ϊ�գ�ɾ��ʧ��
    }
    struct tag* p = *tagHead;
    struct tag* q = NULL;
    while (p != NULL && strcmp(p->name, tagName) != 0) { // ������������Ѱ�ұ�ǩ
        q = p;
        p = p->next;
    }
    if (p == NULL) { // δ�ҵ���ǩ
        return 0;
    }
    if (q == NULL) { // �ҵ��ı�ǩΪ����ͷ
        *tagHead = p->next;
    }
    else { // �ҵ��ı�ǩΪ�����еĽ��
        q->next = p->next;
    }
    free(p); // �ͷ��ڴ�
    return 1; // ɾ���ɹ�
}

// �Ƿ������ǩ���ڲ�����
int isTagContained(struct tag* tagHead, char* tagName) {
    if (tagName == NULL || strlen(tagName) == 0 || tagHead == NULL) {
        return 0; // ��ǩ��Ϊ�ջ�����Ϊ�գ���Ϊδ�ҵ���ǩ
    }
    struct tag* p = tagHead;
    while (p != NULL) { // ��������
        if (strcmp(p->name, tagName) == 0) { // �жϱ�ǩ�Ƿ����
            return 1;
        }
        p = p->next;
    }
    return 0; // δ�ҵ���ǩ
}

// ��ӱʼǱ�ǩ
Status addTagToNote(Note* note, char* tagName) {
    if (note == NULL || tagName == NULL || strlen(tagName) == 0) {
        return ERROR; // �ʼ�Ϊ�ջ��ǩ��Ϊ�գ����ش���״̬
    }
    if (isTagContained(note->tagHead, tagName)) { // ����Ѱ����ñ�ǩ�����ش���״̬
        return ERROR;
    }
    Status status = addTag(&(note->tagHead), tagName); // ����addTag������ӱ�ǩ
    if (status == ERROR) {
        free(status);       // �ͷ�֮ǰ������ڴ�
    }
    return status;
}

// ɾ���ʼǱ�ǩ
Status deleteTagFromNote(Note* note, char* tagName) {
    if (note == NULL || tagName == NULL || strlen(tagName) == 0) {
        return ERROR; // �ʼ�Ϊ�ջ��ǩ��Ϊ�գ����ش���״̬
    }
    if (!isTagContained(note->tagHead, tagName)) { // ���δ�����ñ�ǩ�����ش���״̬
        return ERROR;
    }
    Status status = deleteTag(&(note->tagHead), tagName); // ����deleteTag����ɾ����ǩ
    if (status == ERROR) {
        free(status);       // �ͷ�֮ǰ������ڴ�
    }
    return status;
}

// ��ʾ��ǩ���ڲ�����
void viewTag(struct tag* tagHead) {
    struct tag* p = tagHead;
    while (p != NULL) { // ��������
        printf("%s ", p->name); // �����ǩ��
        p = p->next;
    }
}

// ��ʾָ���ʼǵı�ǩ
Status viewTagsInNote(Note* note)
{
    if (note == NULL) {
        return ERROR; // �ʼ�Ϊ�գ����ش���״̬
    }
    printf("Tags for Note %s: ", note->name); // ����ʼ���
    viewTag(note->tagHead); // ����ñʼǵı�ǩ
    printf("\n");
    return SUCCESS; // ���سɹ�״̬
}

// ����ļ��б�ǩ(ע���ǩ��������⣬�ɹ�����SUCCESS��ʧ�ܷ���ERROR)
Status addTagToFolder(Folder* folder, char* tagName) {
    if (folder == NULL || tagName == NULL) {
        return ERROR;
    }
    Tag* tag = *(folder->tags);
    while (tag != NULL) {
        if (strcmp(tag->name, tagName) == 0) {
            // ��ǩ���Ѵ���
            return ERROR;
        }
        tag = tag->next;
    }
    // �����½ڵ�
    Tag* newTag = (Tag*)malloc(sizeof(Tag));
    if (newTag == NULL) {
        return ERROR;   // �ڴ����ʧ�ܣ����ش���״̬
    }
    strncpy(newTag->name, tagName, 50);
    newTag->next = *(folder->tags);
    *(folder->tags) = newTag;
    return SUCCESS;
}

// ɾ���ļ��б�ǩ
Status deleteTagFromFolder(Folder* folder, char* tagName) {
    if (folder == NULL || tagName == NULL) {
        return ERROR;
    }
    Tag* tag = *(folder->tags);
    Tag* prevTag = NULL;
    while (tag != NULL) {
        if (strcmp(tag->name, tagName) == 0) {
            if (prevTag == NULL) {
                *(folder->tags) = tag->next;
            }
            else {
                prevTag->next = tag->next;
            }
            free(tag);
            return SUCCESS;
        }
        prevTag = tag;
        tag = tag->next;
    }
    // ��ǩ������
    return ERROR;
}

// ��ʾָ���ļ��еı�ǩ
Status viewTagsInFolder(Folder* folder) {
    if (folder == NULL) {
        return ERROR;
    }
    Tag* tag = folder->tags;
    while (tag != NULL) {
        printf("%s\n", tag->name);
        tag = tag->next;
    }
    return SUCCESS;
}
