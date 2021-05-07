//
// Created by Lao·Zhu on 2021/5/6.
//

#ifndef PROGRAM_GUI_GUI_LISTBOX_H_
#define PROGRAM_GUI_GUI_LISTBOX_H_

#define LISTBOX_COLOR_EDGE 0xad56
#define LISTBOX_COLOR_FOCUS 0x03da

typedef struct LISTBOX_ITEM_TYPE_T {
    struct LISTBOX_ITEM_TYPE_T *Previous_ListBox_Item;
    struct LISTBOX_ITEM_TYPE_T *Next_ListBox_Item;
    unsigned char ItemText[21];
    unsigned char ItemNumber;
} ListBox_Item_Struct_t;

typedef struct LISTBOX_TYPE_T {
    unsigned char X_Pos;
    unsigned char Y_Pos;
    unsigned char Width;
    unsigned char Height;
    const char *Text;
    void *NextListBox;
    void (*CallbackFunction)(void *Object, unsigned char Key);
    unsigned char Widget_Type;
    unsigned char ItemIndex;
    unsigned char DisplayIndex;
    ListBox_Item_Struct_t *FirstItem;
} ListBox_Struct_t;

void GUI_ListBoxUpdate(ListBox_Struct_t *ListBox, unsigned char keynum);
void GUI_ListBoxAddItem(ListBox_Struct_t *ListBox, const char *fmt, ...);
void GUI_InitListBox(ListBox_Struct_t *ListBox);

#endif //PROGRAM_GUI_GUI_LISTBOX_H_