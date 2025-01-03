#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>

#define MAX_ETUDIANTS 100
#define MAX_MATIERES 6

char nom_etudiant[MAX_ETUDIANTS][20];
char prenom_etudiant[MAX_ETUDIANTS][20];
int matricule_etudiant[MAX_ETUDIANTS];
float notes[MAX_ETUDIANTS][MAX_MATIERES];
const char *matieres[MAX_MATIERES] = {"Francais", "Anglais", "Informatique", "Electricite", "Circuits", "Droit"};
int compteur_etudiants = 0;

void clearConsole()
{
    system("cls");
}

void MODIFIEREtudiant(int index)
{
    printf("Saisissez le nom de l'etudiant : ");
    scanf("%s", nom_etudiant[index]);
    printf("Saisissez le prenom de l'etudiant : ");
    scanf("%s", prenom_etudiant[index]);

}


int chercherEtudiantParMatricule(int matricule)
{
    int i;

    for (i = 0; i < compteur_etudiants; i++)
    {
        if (matricule_etudiant[i] == matricule)
        {
            return i;
        }
    }
    return -1;
}

void saisirNomPrenomEtudiant(int index)
{
    printf("Saisissez le nom de l'etudiant : ");
    scanf("%s", nom_etudiant[index]);
    printf("Saisissez le prenom de l'etudiant : ");
    scanf("%s", prenom_etudiant[index]);
}

void saisirMatriculeEtudiant(int index)
{
    int matricule;
    int existeDeja;

    do
    {
        printf("Saisissez le matricule de l'etudiant : ");
        scanf("%d", &matricule);

        existeDeja = chercherEtudiantParMatricule(matricule);

        if (existeDeja != -1)
        {
            printf("Ce matricule existe deja. Veuillez en saisir un autre.\n");
        }
    } while (existeDeja != -1);

    matricule_etudiant[index] = matricule;
}

void saisirNoteEtudiant(int index, int matiereIndex)
{
    float note;

    do
    {
        printf("Saisissez la note de l'etudiant pour la matiere %s: ", matieres[matiereIndex]);
        scanf("%f", &note);

        if (note < 0 || note > 20)
        {
            printf("La note doit etre comprise entre 0 et 20.\n");
        }
    } while (note < 0 || note > 20);

    notes[index][matiereIndex] = note;
}

void afficherListeNotes(int matiereIndex)
{
    int i;

    printf("Liste des notes pour la matiere %s:\n", matieres[matiereIndex]);

    for (i = 0; i < compteur_etudiants; i++)
    {
        printf("Etudiant: %s \t %s\n", nom_etudiant[i], prenom_etudiant[i]);
        printf("Note: %.2f\t", notes[i][matiereIndex]);
        printf("-----------------------\n");
    }
    getch();
}

void afficherBulletin(int index)
{
    int i;
    float coefficients[MAX_MATIERES] = {1.5, 1.5, 2, 2, 3, 1};
    float totalNotes = 0;
    float totalCoefficients = 0, n;
    int x = 0;

    printf("Bulletin de l'etudiant: %s %s\n", nom_etudiant[index], prenom_etudiant[index]);
    printf("-----------------------\n");

    for (i = 0; i < MAX_MATIERES; i++)
    {   if(notes[index][i]<10){
        printf("Matiere: %s\t", matieres[i]);
        printf("Coefficient: %.1f\t", coefficients[i]);
        textcolor(YELLOW);
        cprintf("Note: %.2f \t ", notes[index][i]);
        printf("Note x Coefficient: %.2f\t \n", notes[index][i] * coefficients[i]);
        printf("-----------------------\n");
        totalNotes += notes[index][i] * coefficients[i];
        totalCoefficients += coefficients[i];}
        else{
        printf("Matiere: %s \t", matieres[i]);
        printf("Coefficient: %.1f \t", coefficients[i]);
        printf("Note: %.2f \t", notes[index][i]);
        printf("Note x Coefficient: %.2f \t \n", notes[index][i] * coefficients[i]);
        printf("-----------------------\n");
        totalNotes += notes[index][i] * coefficients[i];
        totalCoefficients += coefficients[i];
        }
    }
    n = totalNotes / totalCoefficients;
    if (n < 10){
    for(i=0;i<10;i++)
         {
          Sleep(300);
          gotoxy(50,25);
          textcolor(RED);
          cprintf("\r Moyenne generale: %.2f\n", n);
          gotoxy(50,26);
          textcolor(RED);
          cprintf("Redoublant");
          Sleep(300);
          gotoxy(50,26);
          printf("Redoublant");
          gotoxy(50,25);
          printf("\r Moyenne generale: %.2f\n", n);
         }
    }
    else
    {
        printf("Moyenne generale: %.2f\n", n);
        printf("-----------------------\n");
        if (n >= 10 && n < 12)
        {
            printf("\n");
            printf("\n");
            printf("PASSABLE\n");
        }
        if (n >= 12 && n < 15)
        {
            printf("\n");
            printf("\n");
            printf("ASSEZ BIEN \n");
        }
        if (n >= 15 && n < 16)
        {
            printf("\n");
            printf("\n");
            printf("BIEN \n");
        }
        if (n >= 16)
        {
            printf("\n");
            printf("\n");
            printf("TRES BIEN \n");
        }
    }
    getch();
}

void afficherMenuGestion()
{
    int choix, index, i, matricule;

    do
    {
        clearConsole();

        printf("=== MENU DE GESTION ===\n\n");
        printf("1. Ajouter un etudiant\n");
        printf("2. modifier un etudiant\n");
        printf("3. Saisir les notes d'un etudiant\n");
        printf("4. Retour\n");
        printf("5. QUITER \n");
        printf("Choix: ");
        scanf("%d", &choix);

        switch (choix)
        {
        case 1:
            clearConsole();
            saisirNomPrenomEtudiant(compteur_etudiants);
            saisirMatriculeEtudiant(compteur_etudiants);
            compteur_etudiants++;
            break;

        case 2:
            clearConsole();
            printf("Saisissez le matricule de l'etudiant : ");
            scanf("%d", &matricule);
            index = chercherEtudiantParMatricule(matricule);
            if (index != -1)
            {
                clearConsole();
                MODIFIEREtudiant(index);
            }
            else
            {
                printf("Aucun etudiant avec ce matricule n'a ete trouve.\n");
            }
            break;

        case 3:
            clearConsole();
            printf("Saisissez le matricule de l'etudiant : ");
            scanf("%d", &matricule);
            index = chercherEtudiantParMatricule(matricule);
            if (index != -1)
            {
                clearConsole();
                for (i = 0; i < MAX_MATIERES; i++)
                {
                    saisirNoteEtudiant(index, i);
                }
            }
            else
            {
                printf("Aucun etudiant avec ce matricule n'a ete trouve.\n");
            }
            break;

        case 4:
            return;
            break;
        case 5:
            printf("Au revoir !\n");
            Sleep(1000);
            exit(0);

              break;
        default:
            printf("Choix invalide.\n");
            break;
        }



    } while (choix != 5);
}

void afficherMenuConsultation()
{
    int choix, index, matricule;

    do
    {
        clearConsole();

        printf("=== MENU DE CONSULTATION ===\n\n");
        printf("1. Afficher les notes d'une matiere\n");
        printf("2. Afficher le bulletin d'un etudiant\n");
        printf("3. Retour\n");
        printf("4. QUITER \n");
        printf("Choix: ");
        scanf("%d", &choix);

        switch (choix)
        {
        case 1:
            clearConsole();
            {
                int matiereIndex;
                printf("Saisissez l'index de la matiere : ");
                scanf("%d", &matiereIndex);
                if (matiereIndex >= 0 && matiereIndex < MAX_MATIERES)
                {
                    clearConsole();
                    afficherListeNotes(matiereIndex);
                }
                else
                {
                    printf("Index de matiere invalide.\n");
                }
            }
            break;

        case 2:
            clearConsole();
            printf("Saisissez le matricule de l'etudiant : ");
            scanf("%d", &matricule);
            index = chercherEtudiantParMatricule(matricule);
            if (index != -1)
            {
                clearConsole();
                afficherBulletin(index);
            }
            else
            {
                printf("Aucun etudiant avec ce matricule n'a ete trouve.\n");
            }
            break;

        case 3:
            return;
            break;
         case 4:
            printf("Au revoir !\n");
            Sleep(1000);
            exit(0);

              break;
        default:
            printf("Choix invalide.\n");
            break;
        }

    } while (choix != 4);
}

void afficherMenuPrincipal()
{
    clearConsole();
    printf("=== MENU PRINCIPAL ===\n\n");
    printf("1. Gestion\n");
    printf("2. Consultation\n");
    printf("3. Quitter\n\n");
    printf("Choix: ");
}
//fonction_main
int main()
{
    int choix;

    do
    {
        afficherMenuPrincipal();
        scanf("%d", &choix);

        switch (choix)
        {
        case 1:
            clearConsole();
            afficherMenuGestion();
            break;

        case 2:
            clearConsole();
            afficherMenuConsultation();
            break;

        case 3:
            printf("Au revoir !\n");
            break;

        default:
            printf("Choix invalide. Veuillez reessayer.\n");
            break;
        }

        if (choix != 3)
        {
            printf("\nAppuyez sur une touche pour continuer...\n");
            getchar();
            getchar();
        }

    } while (choix != 3);

    return 0;
}
