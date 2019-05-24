#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "linklist_interface.h"

void list_init(List *list)
{
	list->head = NULL;
	list->tail = NULL;
	list->len = 0;
}

bool is_empty(List *list)
{
	return (list->head == NULL);
}

static struct node *make_node(void *data)    //���û����ݹ��������ݴ��Ϊһ������ڵ�
{
	struct node *n;

	n = malloc(sizeof(struct node));
	assert(n != NULL);

	n->next = NULL;
	n->data = data;

	return n;
}

static void delete_node(List *list, struct node *key)
{
	struct node *n;

	n = list->head;

	if(n == key){
		list->head = n->next;
		list->len--;
		return;
	}

	while(n->next){
		if(n->next == key){
			if(key == list->tail)
				list->tail = n;
			n->next = n->next->next;
			list->len--;
			return;
		}
		n = n->next;
	}
}

static void insert_node(List *list, struct node *key)
{
	if(list->head == NULL){
		list->head = key;
		list->tail = key;
	}else{
		list->tail->next = key;
		list->tail = key;
	}

	list->len++;
}

static struct node *get_node(List *list, int idx)
{
	int i = 0;
	struct node *n;
	n = list->head;

	while(n && i < idx){
		i++;
		n = n->next;
	}

	if(n)
		return n;

	return NULL;
}

void list_insert_at_head(List *list, void *data)    //ͷ�巨
{
	struct node *n;
	n = make_node(data);

	if(list->head == NULL){ //����ǿ�����
		list->head = n;
		list->tail = n;
	}
	else{                   //������Ƿǿ�����
		n->next = list->head;
		list->head = n;
	}
	list->len++;
}

void list_insert_at_index(List *list, void *data, long index)
{
	long i = 1; //��1��ʼ��
	struct node *p, *n;

	p = list->head;

	while(p && i < index){
		p = p->next;
		i++;
	}

	if(p){ //�������������ˣ�����i��û��index��˵����index���ڵ㲻���ڡ�
		n = make_node(data);
		n->next = p->next;
		p->next = n;
		list->len++;
	}
}

void list_insert_at_tail(List *list, void *data)    //β�巨
{
	struct node *n;
	n = make_node(data);

	if(is_empty(list)){    //����ǿ�����
		list->head = n;
		list->tail = n;
	}
	else{                      //������Ƿǿ�����
		list->tail->next = n;
		list->tail = n;
	}
	list->len++;
}

void list_insert(List *list, void *data)    //Ĭ�ϲ���β�巨
{
#if 1
	list_insert_at_tail(list, data);
#else
	struct node *n;

	n = make_node(data);

	if(list->head == NULL){
		list->head = n;
		list->tail = n;
	} else {
		list->tail->next = n;
		list->tail = n;
	}
	list->len++;
#endif
}

void * list_delete(List *list, void *key, int (*compare)(const void *, const void *))
{
	void *data;
	struct node *n, *t;

	if (list_get_length(list) == 0)
		return NULL;

	n = list->head;

	if(!compare(n->data, key)){    //���Ҫɾ���Ľڵ�Ϊ�׽ڵ�
		t = n;
		data = n->data;
		list->head = n->next;
		free(t);
		list->len--;
		return data;
	}

	while(n->next != NULL){        //�������ҷ��������Ľڵ㣬ɾ��֮
		if(compare(n->next->data, key) == 0){    //ֻɾ����һ�����������Ľڵ㡣
			t = n->next;
			if(n->next == list->tail)
				list->tail = n;
			n->next = n->next->next;
			data = t->data;
			free(t);
			list->len--;
			return data;    //��ɾ�������ݷ��ظ��û������û������Ĵ���ʹ�á�
		}
		n = n->next;
	}
	return NULL;    //û�ҵ�ƥ��Ľڵ㣬����NULL
}

void *list_delete_at_index(List *list, long idx)
{
	long i = 1; //��1��ʼ��
	void *data = NULL;
	void *ret = NULL;
	struct node *n = NULL;

	n = get_node(list, idx);

	if (n) {
		data = n->data;
		delete_node(list, n);
		free(n);
	}

	return data;
}

void *list_search(List *list, void *key, int (*compare)(const void *, const void *))
{
	struct node *n;
	n = list->head;

	while(n){
		if(!compare(n->data, key))    //�ҵ��ˣ������ҵ�������
			return n->data;
		n = n->next;
	}

	return NULL;    //�Ҳ���������NULL
}

static struct node *find_min_node(List *list,
				  int (*compare)(const void *, const void *))
{
	struct node *min, *n;

	n = list->head;
	min = list->head;

	while(n){
		if(compare(min->data, n->data) > 0)
			min = n;
		n = n->next;
	}

	return min;
}

void list_sort(List *list,
	       int (*compare)(const void *, const void *))
{
	List tmp;
	struct node *n;

	list_init(&tmp);

	while(! is_empty(list)){
		n = find_min_node(list, compare);
		delete_node(list, n);
		insert_node(&tmp, n);
	}
	list->head = tmp.head;
	list->tail = tmp.tail;
	list->len = tmp.len;
}

void list_traverse(List *list, void (*handle)(void *, void *), void *priv)
{
	struct node *p;

	p = list->head;
	while(p){
		handle(p->data, priv);
		p = p->next;
	}
}

int list_traverse_cond(List *list, int (*handle)(List *list, void *, void *), void *priv)
{
	struct node *p;
	struct node *n;
	int ret;

	p = list->head;
	while(p){
		n = p->next;
		ret = handle(list, p->data, priv);
		if (ret <= 0)
			return ret;

		p = n;
	}

	return 0;
}

void list_reverse(List *list)
{
	struct node *pre = NULL, *next, *p = list->head;

	list->tail = list->head;    //tailָ��head��
	while(p){
		next = p->next;
		if(!next)  //��p->nextΪ���һ���ڵ�ʱ����headָ��p->next
			list->head = p;
		//��¼��ǰ�ڵ�Ϊpre����Ϊ��һ���ڵ��next.��һ���ڵ�ΪNULL����ʼ��ʱ�Ѷ��塣
		p->next = pre;
		pre = p;
		p = next;
	}
}

long list_get_length(List *list)
{
	return (list->len);
}

void *list_get_element(List *list, int idx)
{
	printf("======list_get_element======\n");
	int i = 0;
	struct node *n;
	n = list->head;

	while(n && i < idx){
		i++;
		n = n->next;
	}

	if(n)
		return n->data;

	return NULL;
}

void list_destroy(List *list, void (*destroy)(void *))
{
	struct node *n, *t;
	n = list->head;

	while(n){
		t = n->next;    //tֻ��һ����¼n->next�Ĺ��ܣ���������n free��֮�󣬾��Ҳ���n->next�ˡ�
		if(destroy)  //�����û��Զ�������ݴ�������Ϊ0ʱ��ִ��
			destroy(n->data);    //ʹ���û��ṩ��destroy�������ͷ��û����ݹ��������ݡ�
		free(n);
		n = t;  //��n free��֮���ٰ�t��n���൱�ڰ�n->next��n,���ѭ��������������ɾ����
	}

	list->head = NULL;
	list->tail = NULL;
	list->len = 0;
}

