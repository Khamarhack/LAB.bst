/****************************************
Autor: Santiago Camargo
Fecha: 28 de Agosto 2024
Materia: Estructura de Datos
Tema: implementación BST 
****************************************/

#include <iostream>
#include<stdlib.h>
using namespace std;

struct Nodo{
	int dato; //Dato a almacenar en el raiz
	struct Nodo *left;
	struct Nodo *right; //En cada nodo se relacionan las direcciones con 2 nodos diferentes de izquierda a derechas, formando 2 posibles aristas
};	

struct Nodo *nuevoNodo(int dato){
	struct Nodo *temporal = new struct Nodo();
	temporal->dato = dato;
	temporal->left = temporal->right = NULL;
	return (temporal);
}

/******* Preorder *********/
void preOrdenT(struct Nodo *raiz){
	if (raiz==NULL)
		return;
	cout << raiz->dato << "->"; 
	preOrdenT(raiz->left);
	preOrdenT(raiz->right);
}

/******* Postorder *********/
void postOrdenT(struct Nodo *raiz){
	if (raiz==NULL)
		return;
	postOrdenT(raiz->left);
	postOrdenT(raiz->right);
	cout << raiz->dato << "->"; 
}

/******* Inorder *********/
void inOrdenT(struct Nodo *raiz){
	if (raiz==NULL)
		return;
	inOrdenT(raiz->left);
	cout << raiz->dato << "->"; 
	inOrdenT(raiz->right);
}

/****** Insertar nuevo nodo, dado un valor (BST) ********/
struct Nodo *insertarBST(struct Nodo *nodo, int newDato){
	if (nodo==NULL)
		return nuevoNodo(newDato);
	if (newDato < nodo->dato)
		nodo->left = insertarBST(nodo->left, newDato);
	else
		nodo->right = insertarBST(nodo->right, newDato);

	return nodo;
}


/****** funciÃ³n que retorna el nodo con menor valor en un BST ********/
struct Nodo *minValorNodo(struct Nodo *nodo){
	struct Nodo *actual = nodo;
	/*Se busca iterativamente el elemento menor a la izquierda*/
	while(actual && actual->left !=NULL)
		actual = actual->left;
	return actual;
}


/****** funciÃ³n que elimina un nodo con valor en un BST ********/
struct Nodo *borrarNodo(struct Nodo *nodo, int dato){
	/*=Arbol vacio=*/
	if(nodo == NULL)
		return nodo;
	/*=si el valor es menor a la raiz, ir por la izquierda=*/
	if(dato < nodo->dato)
		nodo->left = borrarNodo(nodo->left, dato);
	/*=si el valor es mayor a la raiz, ir por la derecha=*/
	else if (dato > nodo->dato)
		nodo->right = borrarNodo(nodo->right, dato);
	/*=el valor esta en la misma raiz=*/
	else {
		/*=Nodo con solo un hijo o sin hijos=*/	
		if(nodo->left == NULL){
			struct Nodo *temporal = nodo->right;
			free(nodo);
			return temporal;
		}else if(nodo->right == NULL){
			struct Nodo *temporal = nodo->left;
			free(nodo);
			return temporal;
		}
		/*=Nodo con ambos hijos, tomar el sucesor y borrar el nodo=*/
		struct Nodo *temp = minValorNodo(nodo->right);
		/*=copiar el contenido InOrder sucesor a el nodo=*/
		nodo->dato = temp->dato;
		/*=borrar el InOrder sucesor=*/
		nodo->right = borrarNodo(nodo->right, temp->dato);
	}
	return nodo;
}



int main(){
	struct Nodo *arbol1 = NULL; 
	arbol1 = insertarBST(arbol1, 40);
	arbol1 = insertarBST(arbol1, 30);
	arbol1 = insertarBST(arbol1, 60);
	arbol1 = insertarBST(arbol1, 65);
	arbol1 = insertarBST(arbol1, 70);
	
	cout << "\n -PreOrden ";  
	preOrdenT(arbol1);
	cout << "\n -PostOrden "; 
	postOrdenT(arbol1);
	cout << "\n -InOrden ";
	inOrdenT(arbol1);

	cout << "Se elimina el nodo(40)" << endl;
	arbol1 = borrarNodo(arbol1, 40);
	inOrdenT(arbol1);

	return 0;	
}

