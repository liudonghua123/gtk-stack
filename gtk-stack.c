#include "stack.h"
#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>

// <添加注释>
GtkWidget *listboxContent, *buttonPush, *buttonPop, *buttonExit;
NODE *stack;
DATA element;
GtkWidget *label;
GtkWidget *window;

/**
 * <添加注释>
 */
void initializationUI() {
    GtkBuilder *builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, "gtk-stack.glade", NULL);
    // <添加注释>
    window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
    listboxContent = GTK_WIDGET(gtk_builder_get_object(builder, "listboxContent"));
    buttonPush = GTK_WIDGET(gtk_builder_get_object(builder, "buttonPush"));
    buttonPop = GTK_WIDGET(gtk_builder_get_object(builder, "buttonPop"));
    buttonExit = GTK_WIDGET(gtk_builder_get_object(builder, "buttonExit"));
    // <添加注释>
    gtk_builder_connect_signals(builder, NULL);
    g_object_unref(builder);
    gtk_widget_show(window);
    gtk_main();
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    stack_init(&stack);
    initializationUI();
    return 0;
}

/**
 * <添加注释>
 */
void removeChildOfListBoxContent(GtkWidget *child, gpointer data) {
    gtk_container_remove(GTK_CONTAINER(listboxContent), child);
}

/**
 * <添加注释>
 */
void updateListBoxContent() {
    // 遍历listboxContent中的子组件，执行删除操作，注意第二个参数是一个函数
    gtk_container_foreach(GTK_CONTAINER(listboxContent), removeChildOfListBoxContent, NULL);
    // 定义一个临时栈指针，用于使用top遍历栈中的数据
    NODE *temporaryStack = stack;
    DATA *data;
    while (!empty(temporaryStack)) {
        data = top(temporaryStack);
        temporaryStack = temporaryStack->prev;
        // 把int类型转换为字符串类型（也可以使用其他方法，例如itoa），用作label显示的内容
        char labelTitle[10];
        sprintf(labelTitle, "%d", data->info);
        GtkWidget *label = gtk_label_new(labelTitle);
        gtk_container_add(GTK_CONTAINER(listboxContent), label);
    }
    // IMPORTANT!!!
    // 设置好容器中的子组件之后一定需要调用 gtk_widget_show_all(window) 重新布局显示
    // 否则会出现新增加的子组件高度显示问题
    gtk_widget_show_all(window);
}

/**
 * <添加注释>
 */
G_MODULE_EXPORT void on_window_destroy() {
    // <添加注释>
    gtk_main_quit();
}

/**
 * <添加注释>
 */
G_MODULE_EXPORT void on_buttonPush_clicked() {
    element.info = rand();
    g_print("push element %d into stack\n", element.info);
    stack = push(stack, element);
    updateListBoxContent();
}

/**
 * <添加注释>
 */
G_MODULE_EXPORT void on_buttonPop_clicked() {
    if (!empty(stack)) {
        stack = pop(stack, &element);
        g_print("pop element %d from stack\n", element.info);
        updateListBoxContent();
    } else {
        g_print("stack is empty, no operation processed\n");
    }
}

/**
 * <添加注释>
 */
G_MODULE_EXPORT void on_buttonExit_clicked() { on_window_destroy(); }