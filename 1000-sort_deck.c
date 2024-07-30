#include "deck.h"
#include <stdlib.h>
#include <string.h>

/**
 * get_card_value - Get the numeric value of a card
 * @str: String representation of the card value
 *
 * Return: Numeric value of the card
 */
int get_card_value(const char *str)
{
    int i;
    char *values[] = {"Ace", "2", "3", "4", "5", "6", "7", "8", "9",
                      "10", "Jack", "Queen", "King"};

    for (i = 0; i < 13; i++)
    {
        if (strcmp(str, values[i]) == 0)
            return (i);
    }
    return (0);
}

/**
 * card_cmp - Compare two cards
 * @a: Pointer to the first card
 * @b: Pointer to the second card
 *
 * Return: Difference in values
 */
int card_cmp(const void *a, const void *b)
{
    deck_node_t *node_a = *(deck_node_t **)a;
    deck_node_t *node_b = *(deck_node_t **)b;

    if (node_a->card->kind != node_b->card->kind)
        return (node_a->card->kind - node_b->card->kind);

    return (get_card_value(node_a->card->value) -
            get_card_value(node_b->card->value));
}

/**
 * sort_deck - Sort a deck of cards
 * @deck: Pointer to the head of the deck
 */
void sort_deck(deck_node_t **deck)
{
    int i, count = 0;
    deck_node_t *current;
    deck_node_t **array;

    if (deck == NULL || *deck == NULL)
        return;

    current = *deck;
    while (current != NULL)
    {
        count++;
        current = current->next;
    }

    array = malloc(count * sizeof(deck_node_t *));
    if (array == NULL)
        return;

    current = *deck;
    for (i = 0; i < count; i++)
    {
        array[i] = current;
        current = current->next;
    }

    qsort(array, count, sizeof(deck_node_t *), card_cmp);

    for (i = 0; i < count - 1; i++)
    {
        array[i]->next = array[i + 1];
        array[i + 1]->prev = array[i];
    }
    array[0]->prev = NULL;
    array[count - 1]->next = NULL;
    *deck = array[0];

    free(array);
}
