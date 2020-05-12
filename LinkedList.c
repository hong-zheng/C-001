/*
 *  LinkList 
 * 不带头单向循环链表
 */
#include <stdio.h>
#include <stdlib.h>

typedef int DataType ;
typedef struct Node{
	DataType _data ;
	struct Node* _prev ;
	struct Node* _next ;
}Node;
typedef struct LinkedList{
	Node* _head ;
}LinkedList ;

// 链表初始化
void LinkedListInit( LinkedList* ls ){
	ls->_head = NULL ;
}
Node* createNode( DataType data ){
	Node* node = (Node*)malloc(sizeof(Node));
	node->_data = data ;
	node->_prev = NULL ;
	node->_next = NULL ;
}
// 链表尾插
void LinkedListPushBack( LinkedList* ls , DataType data ){
	Node* node = createNode( data ) ;
	if( ls->_head == NULL ){
		ls->_head = node ;
		node->_next = ls->_head ;
		node->_prev = ls->_head ;
	}else{
		Node* last = ls->_head->_prev ;
		node->_prev = last ;
		node->_next = ls->_head ;
		last->_next = node ;
		ls->_head->_prev = node ;
	}
}
/*
 * 头插
 */
void LinkedListPushFront( LinkedList* ls , DataType data ){
	Node* node = createNode( data ) ;
	if( ls->_head == NULL ){
		ls->_head = node ;
		node->_next = ls->_head ;
		node->_prev = ls->_head ;
	}else{
		Node* last = ls->_head->_prev ;
		node->_next = ls->_head ;
		ls->_head->_prev = node ;
		node->_prev = last ;
		last->_next = node ;
		ls->_head =  node ;
	}
}
/*
 * 尾删
 */
void LinkedListEraseBack( LinkedList* ls ){
	// 链表为NULL
	if( ls->_head == NULL )
		return ; 
	// 如果链表只有一个节点
	if( ls->_head == ls->_head->_next ){
		free( ls->_head ) ;
		ls->_head = NULL ;
	}else{// 链表多个节点
		Node* last = ls->_head->_prev ;
		Node* prev = last->_prev ;
		prev->_next = ls->_head ;
		ls->_head->_prev = prev ;
		free( last ) ;
	}
}
/*
 * 头删
 */
void LinkedListEraseFront( LinkedList* ls ){
	if( ls->_head == NULL ){
		printf("LinkedList is NULL!\n") ;
		return ;
	}
	if( ls->_head == ls->_head->_next ){	
		free( ls->_head ) ;
		ls->_head = NULL ;
	}else{
		Node* last = ls->_head->_prev ;
		free( ls->_head ) ;
		ls->_head = ls->_head->_next ;
		ls->_head->_prev = last ;
		last->_next = ls->_head ;
	}
}
// 打印链表
void printLinkedList( LinkedList* ls ){
	if( ls->_head == NULL  ){
		printf("链表为空！\n") ;
		return ;
	}
	Node* cur = ls->_head ;
	printf( "%d " , cur->_data ) ;
	while( cur->_next != ls->_head ){
		cur = cur->_next ;
		printf("%d " , cur->_data ) ;
	}	
	printf("\n") ;
}
/*
 * find value in LinkedList
 */
Node* findValue( LinkedList* ls , DataType value){
	if( ls->_head == NULL )
		return ;	
	Node* cur = ls->_head ;
	if( cur->_data == value )
		return cur ;
	while( cur->_next != ls->_head ){
		cur = cur->_next ;
		if( cur->_data == value )
			return cur ;
	}
	printf("[%d] is't in LinkedList!\n" , value ) ;
	return NULL ;
}
/*
 * the number of  element int LinkedList
 */
int LinkedListSize( LinkedList* ls ){
	size_t size = 0 ;
	if( ls->_head == NULL )
		return size ;
	Node* cur = ls->_head ;
	do{
		++size ;
		cur = cur->_next ;
	}while(cur != ls->_head ) ;
	return size ;
} 
/*
 * isEmpty
 */
int isEmpty( LinkedList* ls ){
	if( ls->_head == NULL )
		return 1 ;
	return 0 ;
}
/*
 * destory
 */
void LinkedListDestory( LinkedList* ls ){
	if( ls->_head == NULL ) return ;
	Node* cur = ls->_head ;
	Node* next = cur->_next ;
	while( next != ls->_head ){
		free( cur ) ;
		cur = next ;
		next = cur->_next ;
	}
	free( cur ) ;
	printf("LinkedList is destoryed!\n") ;
}
/*
 * find on the basis of index
 */
Node* findOfIndex( LinkedList* ls , int index ){
	if( isEmpty( ls ) )
		return NULL ;
	if( index > LinkedListSize( ls ) ) return NULL ;
	Node* cur = ls->_head ;
	index--;
	while( index-- )
		cur = cur->_next ;
	return cur ; 
}
void test(){
	LinkedList ls ;
	LinkedListInit( &ls ) ;
	printf("检验链表尾插:>\n") ;
	LinkedListPushBack( &ls , 1 ) ;
	LinkedListPushBack( &ls , 2 ) ;
	LinkedListPushBack( &ls , 3 ) ;
	LinkedListPushBack( &ls , 4 ) ;
	printLinkedList( &ls ) ;
	printf("the number of element in LinkedList is %d!\n",LinkedListSize(&ls)) ;
	Node* findIndex = findOfIndex( &ls , 5 ) ;
	if( findIndex )
		printf("index:[%d]:emlement:[%d]\n",5,findIndex->_data ) ;
	else
		printf("indx:NULL!\n");
	LinkedListDestory( &ls ) ;
/*
	printf("检验链表头插:>\n") ;
	LinkedListPushFront( &ls , 5 ) ; 
	LinkedListPushFront( &ls , 6 ) ; 
	LinkedListPushFront( &ls , 7 ) ; 
	LinkedListPushFront( &ls , 8 ) ; 
	printLinkedList( &ls ) ;
	printf("testFind:>\n") ;
	Node* keynode = findValue( &ls , 8 ) ;
	if( keynode ){
		printf("value = %d\n",keynode->_data);
	}
	keynode = findValue( &ls , 18 ) ;
	if( keynode ){
		printf("value = %d\n",keynode->_data);
	}
	printf("检验尾删:>\n") ;
	LinkedListEraseBack( &ls ) ;
	printLinkedList( &ls ) ;
	LinkedListEraseBack( &ls ) ;
	printLinkedList( &ls ) ;
	LinkedListEraseFront( &ls ) ;
	printLinkedList( &ls ) ;
	LinkedListEraseFront( &ls ) ;
	printLinkedList( &ls ) ;
	LinkedListEraseFront( &ls ) ;
	printLinkedList( &ls ) ;
	LinkedListEraseFront( &ls ) ;
	printLinkedList( &ls ) ;
	LinkedListEraseFront( &ls ) ;
	printLinkedList( &ls ) ;
	LinkedListEraseFront( &ls ) ;
	printLinkedList( &ls ) ;
	if( isEmpty(&ls ) )
		printf("LinkedList is NULL!\n") ;
*/
/*
	LinkedListEraseBack( &ls ) ;
	printLinkedList( &ls ) ;
	LinkedListEraseBack( &ls ) ;
	printLinkedList( &ls ) ;
	LinkedListEraseBack( &ls ) ;
	printLinkedList( &ls ) ;
	LinkedListEraseBack( &ls ) ;
	printLinkedList( &ls ) ;
	LinkedListEraseBack( &ls ) ;
	printLinkedList( &ls ) ;
	LinkedListEraseBack( &ls ) ;
	printLinkedList( &ls ) ;
*/
}
int main( void ){
	test() ;
	printf("zheng hong \n");
	return 0 ;
}
