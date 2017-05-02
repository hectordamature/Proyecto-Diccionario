// convertir Txt2Bin.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Dict {
	char palIngles [50];
	char palEspanol [50];
};

typedef struct Dict TipoDict;

struct Nodo {
	TipoDict info;
	struct Nodo *siguiente; 
};
typedef struct Nodo TipoNodo;
//TipoNodo *lista=NULL;

void convertirtxtBin(char *nombreTxt, char * nombreBin){
	FILE *mnjTxt, *mnjBin;
	char *tmpIngles, *tmpEspanol, linea[200];
	TipoDict tmpDict;
	mnjTxt= fopen (nombreTxt, "r");
	mnjBin=fopen (nombreBin, "wb");
	while (fgets (linea,200,mnjTxt)!=NULL){
		//char *fgets (apunBuffer, numBytes, archivo)	
		tmpIngles= strtok (linea,":");
		tmpEspanol=strtok(NULL, "\n");
		if( strlen(tmpIngles)<50 && strlen(tmpEspanol)<50){
			strcpy (tmpDict.palEspanol,tmpIngles);
			strcpy (tmpDict.palIngles,tmpEspanol);
			fwrite(&tmpDict,sizeof(tmpDict),1,mnjBin);
		//int fwrite (apunBuffer,tamañoBloque,nVeces, ,mnjArchivo)
		}
	}
	fclose (mnjTxt); 
	fclose (mnjBin);
}

void imprimirBin (char *nombreBin){
	FILE *mnjBin = fopen (nombreBin,"rb");
	TipoDict *tmpDict= ((TipoDict*)malloc(sizeof(TipoDict)));
	//int fread(apunBuffer,tamañoBytes,nVeces,mnjArchivos);
	while (fread(tmpDict,sizeof(TipoDict),1,mnjBin)==1){
		//printf("<%s> <%s> \n",tmpDict->palIngles, tmpDict ->palEspanol);
	}
	fclose(mnjBin);
}

char *Search (char *palabra){
	char linea[100];
	char *s1, *s2, *res;
	FILE *manejador;
	manejador= fopen ("palabras.txt", "r");
	printf("\n");
	while (!feof(manejador)){
		res= fgets(linea,100,manejador);
		s1= strtok(linea, ":");
		s2= strtok(NULL, "\n");
		if (res ==NULL){
			break;
		} 
		else if (strcmp(palabra,s1)==0) {
			printf("#### TRADUCCION ####\n");
			printf("    %s = %s \n",s1, s2);
			printf("\n");
		}
	}
	return (s2);
	fclose (manejador);
}

TipoDict palabranueva(){
	TipoDict nuevodict;
	char palabra[50], traduccion[50];
	printf("Introdusca la palabra a añadir en ingles: ");
	scanf("%s", palabra);
	printf("Introdusca ahora la traduccion en español de la palabra anterior: ");
	scanf("%s", traduccion);
	strcpy(nuevodict.palIngles, palabra);
	strcpy(nuevodict.palEspanol, traduccion);
	return nuevodict;
}

TipoNodo * crearNodo (TipoDict elemento){
	TipoNodo *nodito;
	nodito=(TipoNodo *)malloc (sizeof(TipoNodo));
	strcpy (nodito ->info.palIngles, elemento.palIngles);
	strcpy(nodito->info.palEspanol,elemento.palEspanol);
	nodito ->siguiente=NULL;
	return nodito;
}
TipoNodo * adicionarLista (TipoDict elemento, TipoNodo *lst){
	TipoNodo *tmpNodo= crearNodo (elemento); 
	TipoNodo *p;
	if (lst==NULL){
		lst=tmpNodo;
	}
	else {
		p=lst;
		// CAMBIO
		while (p->siguiente !=NULL){
			p=p->siguiente;
		}
		p->siguiente=tmpNodo;
	}
	return lst;	
}

TipoNodo * adicionarListanueva (TipoDict elemento, TipoNodo *lst){
	TipoNodo *tmpNodo= crearNodo (elemento); 
	TipoNodo *p, *s;
	if (lst==NULL){
		lst=tmpNodo;
	}
	else {
		p=lst;
		s=lst->siguiente;
		while (strcmp(p->info.palIngles, s->info.palIngles)!=-1){
			p=p->siguiente;
			s=s->siguiente;
		}
		p->siguiente=tmpNodo;
	}
	return lst;	
}

TipoNodo* cargarDictaLista(char *nombreArch,TipoNodo *lst){
	FILE *mnjArch=fopen (nombreArch, "r");
	TipoDict registro;
	TipoNodo *lista;
	// CAMBIO
	//lista=(TipoNodo *)malloc (sizeof(TipoNodo));
	while (fread(&registro,sizeof(TipoDict),1,mnjArch)==1){
		//printf ("<%s>:<%s>\n",registro.palIngles, registro.palEspanol);
		lst=adicionarLista (registro,lst);
	}
	fclose (mnjArch);
	return (lst);
}

void imprimirLista (TipoNodo *lst){
	TipoNodo *p=lst;

	while (p !=NULL){
		
		printf("%s : %s\n", p->info.palIngles, p->info.palEspanol);
		p=p->siguiente;
	}
}

void Buscarlista(TipoNodo *lst, char *Palab){
	int i;
	char *Pespanol, *Pingles;
	TipoNodo *p=lst;
	while (p !=NULL){
		Pespanol=p->info.palEspanol;
		Pingles=p->info.palIngles;
		if(strcmp(Pingles, Palab)==0){
			printf("\n#### TRADUCCION ####\n");
			printf("     %s : %s\n", Pingles, Pespanol );
			i=-1;
			break;
		}
		else if(strcmp(Pespanol, Palab)==0){
			printf("\n#### TRADUCCION ####\n");
			printf("     %s : %s\n", Pespanol, Pingles);
			i=-1;
			break;
		}
		else if(i==-1){
			break;
		}
		p=p->siguiente;
	}
}


TipoNodo * modificarpalabra(TipoNodo *lst, int pos){
	TipoNodo *p=lst;
	char Frase[50], Frasespa[50], decision;
	int cont=1;
	printf("Escriba la modificacion de la traduccion: ");
	scanf("%s", Frase);
	if (pos==1){
		strcpy(p->info.palEspanol, Frase);
	}
	else {

		while (cont<pos){
			p=p->siguiente;
			cont ++;
		}
		strcpy(p->info.palEspanol, Frase);
	}
	return lst;
}


TipoNodo * Busquedaint(TipoNodo *lst, int pos){
	TipoNodo *p=lst;
	TipoNodo *s=lst->siguiente;
	int cont=1, i;
	while (cont<pos-2){
		p=p->siguiente;
		s=s->siguiente;
		cont ++;
	}
	printf("Tal vez quiso decir: \n");
	printf("%s\n", p->info.palIngles);
	printf("%s\n", s->info.palIngles);
	for(i=0; i<3; i++){
	s=s->siguiente;
	printf("%s\n", s->info.palIngles);
	}
	return lst;
}


TipoNodo * InsertarLista (TipoNodo *lst, int pos, TipoDict elemento){
	TipoNodo *p=lst;
	TipoNodo *q= crearNodo (elemento);
	int cont=1;
	if (pos==1){
		q->siguiente=p;
		lst=q;
	}
	else {

		while (cont<pos-1){
			p=p->siguiente;
			cont ++;
		}
		q->siguiente=p->siguiente;
		p->siguiente=q;
	}
	return lst;
}

TipoNodo * Eliminarpalabra (TipoNodo *lst, int pos){
	TipoNodo *p=lst;
	TipoNodo *s=lst->siguiente;
	int cont=1;
	if (pos==1){
		p->siguiente=s->siguiente;
		lst=p;
	}
	else {

		while(cont<pos-1){
			p=p->siguiente;
			s=s->siguiente;
			cont ++;
		}
		p->siguiente=s->siguiente;
	}
	return lst;
}

int buscarPos (char *palabra, TipoNodo *lst){
	int cont=0;
	char palIngles [50];
	TipoNodo *p=lst;
	if (lst== NULL){
		return 1;
	}
	else {
		do{
			if (p->siguiente==	NULL){
				return cont+1;
			}
			strcpy (palIngles,p->info.palIngles);
			cont ++;
			p=p->siguiente;
		} while (strcmp(palabra,palIngles)>0);
	}
	return cont;
}

void guardarlistaarchivo(TipoNodo *lst,char *nombrearchivo){
	FILE *mnjbin=fopen(nombrearchivo,"wb");
	FILE *mnjtxt=fopen("backup.txt","w");
	TipoNodo *p =lst;
	TipoDict *tmpinfo;
	char cadena[150];
	while (p != NULL){
		tmpinfo=&(p->info);
		fwrite(tmpinfo,sizeof(TipoDict),1,mnjbin);
		sprintf(cadena,"<%s>:<%s>\n",tmpinfo->palIngles,tmpinfo->palEspanol);
		fputs(cadena,mnjtxt);
		p=p->siguiente;
	}
	fclose(mnjbin);
	fclose(mnjtxt);
}
void Menu(TipoNodo *lst){
	int i;
	char Eleccion, Frase[50];
	TipoDict nuevo;
	printf("\n#==== DICCIONARIO INGLES-ESPAÑOL & ESPAÑOL-INGLES ====#\nBienvenido al menu del diccionario, escoja una de las opciones predeterminadas\n s: Salir \n b: Busqueda exacta \n a: Adicionar \n e: Eliminar \n m: Modificar \n i: Busqueda inteligente \nQue opcion desea realizar?: ");
	fflush(stdin);
	scanf("%c", &Eleccion);
	if(Eleccion=='s'){
		printf("Gracias por usar nuestro traductor :)\n");
	}
	else if(Eleccion=='b'){
		printf("Introdusca la frase a traducir: ");
		scanf("%s", Frase);
		Buscarlista(lst, Frase);
	}
	else if(Eleccion=='a'){
			nuevo= palabranueva();
			i=buscarPos(nuevo.palIngles, lst);
			InsertarLista(lst, i, nuevo);
			guardarlistaarchivo(lst,"texto.bin");
	}
	else if(Eleccion=='e'){
			printf("Que palabra en ingles desea eliminar?: ");
			scanf("%s", Frase);
			i=buscarPos(Frase, lst);
			Eliminarpalabra(lst, i);
			guardarlistaarchivo(lst,"texto.bin");
	}
	else if(Eleccion=='m'){
			printf("A que palabra quiere modificarle su traduccion?: ");
			scanf("%s", Frase);
			i=buscarPos(Frase, lst);
			modificarpalabra(lst, i);
			guardarlistaarchivo(lst, "texto.bin");
	}
	else if(Eleccion=='i'){
			printf("Introdusca la frase a traducir: ");
			scanf("%s", Frase);
			i=buscarPos(Frase, lst);
			Busquedaint(lst, i);
	}
}
int main (int argc, char * argv[]){
	TipoNodo *lista=NULL;
	TipoDict nuevo;
	char * palabra= argv[1];
	int i;
	//convertirtxtBin("palabras.txt","palabras.bin");
	//imprimirBin ("palabras.bin");
	//printf("\n");
	lista=cargarDictaLista ("palabras.bin",lista);
	//Buscarlista(lista, palabra);
	if(palabra==NULL){
			Menu(lista);
	}
	else{
		Buscarlista(lista, palabra);
		//char *resultado=Search(palabra);
	}
	//Search (palabra);
	return 0;
}


