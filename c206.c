
/* c206.c **********************************************************}
{* Téma: Dvousměrně vázaný lineární seznam
**
**                   Návrh a referenční implementace: Bohuslav Křena, říjen 2001
**                            Přepracované do jazyka C: Martin Tuček, říjen 2004
**                                            Úpravy: Kamil Jeřábek, září 2018
**
** Implementujte abstraktní datový typ dvousměrně vázaný lineární seznam.
** Užitečným obsahem prvku seznamu je hodnota typu int.
** Seznam bude jako datová abstrakce reprezentován proměnnou
** typu tDLList (DL znamená Double-Linked a slouží pro odlišení
** jmen konstant, typů a funkcí od jmen u jednosměrně vázaného lineárního
** seznamu). Definici konstant a typů naleznete v hlavičkovém souboru c206.h.
**
** Vaším úkolem je implementovat následující operace, které spolu
** s výše uvedenou datovou částí abstrakce tvoří abstraktní datový typ
** obousměrně vázaný lineární seznam:
**
**      DLInitList ...... inicializace seznamu před prvním použitím,
**      DLDisposeList ... zrušení všech prvků seznamu,
**      DLInsertFirst ... vložení prvku na začátek seznamu,
**      DLInsertLast .... vložení prvku na konec seznamu,
**      DLFirst ......... nastavení aktivity na první prvek,
**      DLLast .......... nastavení aktivity na poslední prvek,
**      DLCopyFirst ..... vrací hodnotu prvního prvku,
**      DLCopyLast ...... vrací hodnotu posledního prvku,
**      DLDeleteFirst ... zruší první prvek seznamu,
**      DLDeleteLast .... zruší poslední prvek seznamu,
**      DLPostDelete .... ruší prvek za aktivním prvkem,
**      DLPreDelete ..... ruší prvek před aktivním prvkem,
**      DLPostInsert .... vloží nový prvek za aktivní prvek seznamu,
**      DLPreInsert ..... vloží nový prvek před aktivní prvek seznamu,
**      DLCopy .......... vrací hodnotu aktivního prvku,
**      DLActualize ..... přepíše obsah aktivního prvku novou hodnotou,
**      DLSucc .......... posune aktivitu na další prvek seznamu,
**      DLPred .......... posune aktivitu na předchozí prvek seznamu,
**      DLActive ........ zjišťuje aktivitu seznamu.
**
** Při implementaci jednotlivých funkcí nevolejte žádnou z funkcí
** implementovaných v rámci tohoto příkladu, není-li u funkce
** explicitně uvedeno něco jiného.
**
** Nemusíte ošetřovat situaci, kdy místo legálního ukazatele na seznam 
** předá někdo jako parametr hodnotu NULL.
**
** Svou implementaci vhodně komentujte!
**
** Terminologická poznámka: Jazyk C nepoužívá pojem procedura.
** Proto zde používáme pojem funkce i pro operace, které by byly
** v algoritmickém jazyce Pascalovského typu implemenovány jako
** procedury (v jazyce C procedurám odpovídají funkce vracející typ void).
**/

#include "c206.h"

int errflg;
int solved;

void DLError() {
/*
** Vytiskne upozornění na to, že došlo k chybě.
** Tato funkce bude volána z některých dále implementovaných operací.
**/	
    printf ("*ERROR* The program has performed an illegal operation.\n");
    errflg = TRUE;             /* globální proměnná -- příznak ošetření chyby */
    return;
}

void DLInitList (tDLList *L) {
/*
** Provede inicializaci seznamu L před jeho prvním použitím (tzn. žádná
** z následujících funkcí nebude volána nad neinicializovaným seznamem).
** Tato inicializace se nikdy nebude provádět nad již inicializovaným
** seznamem, a proto tuto možnost neošetřujte. Vždy předpokládejte,
** že neinicializované proměnné mají nedefinovanou hodnotu.
**/

    //aktualizace vseho na NULL
	L->Act = NULL;
	L->First = NULL;
	L->Last = NULL;

}

void DLDisposeList (tDLList *L) {
/*
** Zruší všechny prvky seznamu L a uvede seznam do stavu, v jakém
** se nacházel po inicializaci. Rušené prvky seznamu budou korektně
** uvolněny voláním operace free. 
**/

//dokud je v seznamu položka
    while(L->First != NULL)
    {
        //rušení aktuálního
        if(L->First == L->Act){

            L->Act = NULL;
        }
        //ruseni posledniho
        if(L->First == L->Last){
            L->Last = NULL;
        }
        //přiřazení rušeného do pom
        tDLElemPtr pom = L->First;
        L->First = L->First->rptr;
        // uvolnění pom
        free(pom);

    }
}

void DLInsertFirst (tDLList *L, int val) {
/*
** Vloží nový prvek na začátek seznamu L.
** V případě, že není dostatek paměti pro nový prvek při operaci malloc,
** volá funkci DLError().
**/

    tDLElemPtr EP = malloc(sizeof(struct tDLElem));
    if(EP == NULL){
        DLError();
    }
    else
    {
        EP->data = val;
        EP->rptr = L->First;
        EP->lptr = NULL;
        //pokud není prvně vložený
        if(L->Last != NULL)
        {
            L->First->lptr = EP;
        }
        else
        {
            L->Last = EP ;
        }
        L->First = EP;
    }


}

void DLInsertLast(tDLList *L, int val) {
/*
** Vloží nový prvek na konec seznamu L (symetrická operace k DLInsertFirst).
** V případě, že není dostatek paměti pro nový prvek při operaci malloc,
** volá funkci DLError().
**/

    tDLElemPtr EP =  malloc(sizeof(struct tDLElem));
    //pokud se alokace nezdarila
    if(EP == NULL)
    {
        DLError();
    }
    else
    {
        EP->data = val;
        EP->rptr = NULL;
        EP->lptr = L->Last;
        // pokud nevkládáme první prvek
        if(L->First != NULL)
        {
            L->Last->rptr = EP;
        }
        else
        {
            L->First = EP ;
        }
        L->Last = EP;
    }

}

void DLFirst (tDLList *L) {
/*
** Nastaví aktivitu na první prvek seznamu L.
** Funkci implementujte jako jediný příkaz (nepočítáme-li return),
** aniž byste testovali, zda je seznam L prázdný.
**/


    L->Act = L->First;
}

void DLLast (tDLList *L) {
/*
** Nastaví aktivitu na poslední prvek seznamu L.
** Funkci implementujte jako jediný příkaz (nepočítáme-li return),
** aniž byste testovali, zda je seznam L prázdný.
**/


    L->Act = L->Last;
}

void DLCopyFirst (tDLList *L, int *val) {
/*
** Prostřednictvím parametru val vrátí hodnotu prvního prvku seznamu L.
** Pokud je seznam L prázdný, volá funkci DLError().
**/

    //pokud je seznam prázdný
	if(L->First == NULL)
    {
        DLError();
    }
    else
    {
        * val = L->First->data;
    }


}

void DLCopyLast (tDLList *L, int *val) {
/*
** Prostřednictvím parametru val vrátí hodnotu posledního prvku seznamu L.
** Pokud je seznam L prázdný, volá funkci DLError().
**/

    //pokud je seznam prázdný
    if(L->First == NULL)
    {
        DLError();
    }
    else
    {
        * val = L->Last->data;
    }


}

void DLDeleteFirst (tDLList *L) {
/*
** Zruší první prvek seznamu L. Pokud byl první prvek aktivní, aktivita 
** se ztrácí. Pokud byl seznam L prázdný, nic se neděje.
**/
	
	tDLElemPtr EP;
    //pokud seznam není prázdný
	if(L->First != NULL)
	{
	    EP = L->First;
	    // pokud je první aktivní
	    if(L->Act == L->First)
	    {
	        L->Act = NULL;
	    }
	    // pokud je jedne prvek
	    if(L->First == L->Last)
        {
            L->First = NULL;
            L->Last = NULL;
        }
        else
        {
            L->First = EP->rptr;
            L->First->lptr = NULL;
        }
        free(EP);
	}
}	

void DLDeleteLast (tDLList *L) {
/*
** Zruší poslední prvek seznamu L. Pokud byl poslední prvek aktivní,
** aktivita seznamu se ztrácí. Pokud byl seznam L prázdný, nic se neděje.
**/

    tDLElemPtr EP;
    //pokud seznam není prázdný
    if(L->First != NULL)
    {
        EP = L->Last;
        // poku je aktivní poslední
        if(L->Act == L->Last)
        {
            L->Act = NULL;
        }
        // pokud je jeden prvek
        if(L->First == L->Last)
        {
            L->First = NULL;
            L->Last = NULL;
        }
        else
        {
            L->Last = EP->lptr;
            L->Last->rptr = NULL;
        }
        free(EP);
    }
}

void DLPostDelete (tDLList *L) {
/*
** Zruší prvek seznamu L za aktivním prvkem.
** Pokud je seznam L neaktivní nebo pokud je aktivní prvek
** posledním prvkem seznamu, nic se neděje.
**/

    tDLElemPtr ep;// tElem * ep
    //ep = pomocna promena

    //je aktivní
    if(L->Act != NULL){
        //aktivní není poslední
        if(L->Act->rptr != NULL){
            ep = L->Act->rptr;
            // pokud je rušený poslední
            if(ep == L->Last)
            {
                L->Last = L->Act;
            }
            else
            {
                L->Act->rptr = L->Act->rptr->rptr;

            }
            free(ep);
        }
    }
}

void DLPreDelete (tDLList *L) {
/*
** Zruší prvek před aktivním prvkem seznamu L .
** Pokud je seznam L neaktivní nebo pokud je aktivní prvek
** prvním prvkem seznamu, nic se neděje.
**/

    tDLElemPtr ep;// tElem * ep
    //ep = pomocna promena

    //je aktivní
    if(L->Act != NULL){
        //aktivní není první
        if(L->Act->lptr != NULL){
            ep = L->Act->lptr;
            // pokud je rušený první
            if(ep == L->First)
            {
                L->First = L->Act;
            }
            else
            {
                L->Act->lptr = L->Act->lptr->lptr;

            }
            free(ep);
        }
    }
}

void DLPostInsert (tDLList *L, int val) {
/*
** Vloží prvek za aktivní prvek seznamu L.
** Pokud nebyl seznam L aktivní, nic se neděje.
** V případě, že není dostatek paměti pro nový prvek při operaci malloc,
** volá funkci DLError().
**/
	
	if(L->Act != NULL)
    {
        tDLElemPtr EP = malloc(sizeof(struct tDLElem));
        // nezdařený malloc
        if(EP == NULL){
            DLError();
        }
        else
        {
            EP->data = val;
            EP->lptr = L->Act;
            EP->rptr = L->Act->rptr;
            L->Act->rptr = EP;
            if(L->Act == L->Last)
            {
                L->Last = EP;
            }
            else
            {
                EP->rptr->lptr = EP;
            }
        }

    }

}

void DLPreInsert (tDLList *L, int val) {
/*
** Vloží prvek před aktivní prvek seznamu L.
** Pokud nebyl seznam L aktivní, nic se neděje.
** V případě, že není dostatek paměti pro nový prvek při operaci malloc,
** volá funkci DLError().
**/

    if(L->Act != NULL)
    {
        tDLElemPtr EP = malloc(sizeof(struct tDLElem));
        // nezdařený malloc
        if(EP == NULL){
            DLError();
        }
        EP->data = val;
        EP->lptr = L->Act->lptr;
        EP->rptr = L->Act;
        L->Act->lptr = EP;
        if(L->Act == L->First)
        {
            L->First = EP;
        }
        else
        {
            EP->lptr->rptr = EP;
        }
    }
}

void DLCopy (tDLList *L, int *val) {
/*
** Prostřednictvím parametru val vrátí hodnotu aktivního prvku seznamu L.
** Pokud seznam L není aktivní, volá funkci DLError ().
**/
		
	if(L->Act == NULL)
    {
        DLError();
    }
	else
    {
        *val = L->Act->data;
    }

}

void DLActualize (tDLList *L, int val) {
/*
** Přepíše obsah aktivního prvku seznamu L.
** Pokud seznam L není aktivní, nedělá nic.
**/

    if(L->Act != NULL)
    {
        L->Act->data = val;
    }

}

void DLSucc (tDLList *L) {
/*
** Posune aktivitu na následující prvek seznamu L.
** Není-li seznam aktivní, nedělá nic.
** Všimněte si, že při aktivitě na posledním prvku se seznam stane neaktivním.
**/
	
	if(L->Act != NULL)
    {
        if(L->Act == L->Last)
        {
            L->Act = NULL;
        }
        else
        {
            L->Act = L->Act->rptr;
        }

    }

}


void DLPred (tDLList *L) {
/*
** Posune aktivitu na předchozí prvek seznamu L.
** Není-li seznam aktivní, nedělá nic.
** Všimněte si, že při aktivitě na prvním prvku se seznam stane neaktivním.
**/

    if(L->Act != NULL)
    {
        if(L->Act == L->First)
        {
            L->Act = NULL;
        }
        else
        {
            L->Act = L->Act->lptr;
        }

    }


}

int DLActive (tDLList *L) {
/*
** Je-li seznam L aktivní, vrací nenulovou hodnotu, jinak vrací 0.
** Funkci je vhodné implementovat jedním příkazem return.
**/
	
	
    return(L->Act != NULL);
}

/* Konec c206.c*/
