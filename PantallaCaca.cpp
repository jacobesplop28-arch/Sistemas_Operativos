
#include "PantallaCaca.h"
#include <caca.h>
#include <vector>
#include <string>

// Utilidad interna: dibuja un vector de lineas centrado en el lienzo
static void dibujarCentrado(caca_canvas_t* cv, const std::vector<std::string>& lineas) {
    int anchoLienzo = caca_get_canvas_width(cv);
    int altoLienzo  = caca_get_canvas_height(cv);

    // Calcular ancho maximo de las lineas
    int anchoMax = 0;
    for (const auto& l : lineas) {
        int w = caca_utf8_to_utf32(l.c_str(), nullptr); // cuenta caracteres UTF-8
        if (w > anchoMax) anchoMax = w;
    }

    int altoArte = static_cast<int>(lineas.size());

    // Coordenadas para centrar
    int x0 = (anchoLienzo - anchoMax) / 2;
    int y0 = (altoLienzo - altoArte) / 2;
    if (x0 < 0) x0 = 0;
    if (y0 < 0) y0 = 0;

    for (int i = 0; i < altoArte; ++i) {
        caca_put_str(cv, x0, y0 + i, lineas[i].c_str());
    }
}

// Utilidad interna: espera hasta que se presione ESPACIO
static void esperarEspacio(caca_display_t* dp, caca_canvas_t* cv) {
    // Mensaje inferior
    int ancho = caca_get_canvas_width(cv);
    int alto  = caca_get_canvas_height(cv);
    const char* msg = "Presione ESPACIO para continuar...";
    int x = (ancho - static_cast<int>(caca_utf8_to_utf32(msg, nullptr))) / 2;
    if (x < 0) x = 0;
    caca_put_str(cv, x, alto - 2, msg);
    caca_refresh_display(dp);

    caca_event_t ev;
    while (true) {
        if (caca_get_event(dp, CACA_EVENT_KEY_PRESS, &ev, -1)) {
            int tecla = caca_get_event_key_ch(&ev);
            if (tecla == ' ' || tecla == CACA_KEY_RETURN) break; // ESPACIO o Enter
        }
    }
}

void PantallaCaca::mostrarBienvenida() {
    caca_canvas_t* cv = nullptr;
    caca_display_t* dp = caca_create_display(nullptr);
    if (!dp) return;
    cv = caca_get_canvas(dp);

    caca_set_color_ansi(cv, CACA_LIGHTGREEN, CACA_BLACK);
    caca_clear_canvas(cv);

    // --- Dibujo de prueba de bienvenida ---
    std::vector<std::string> arte = {
        "  _____ _                 _       ",
        " / ____(_)               | |      ",
        "| (___  _ _ __ ___  _   _| | __ _ ",
        " \\___ \\| | '_ ` _ \\| | | | |/ _` |",
        " ____) | | | | | | | |_| | | (_| |",
        "|_____/|_|_| |_| |_|\\__,_|_|\\__,_|",
        "",
        "   SIMULADOR DE MEMORIA Y RR",
        "          Equipo 10"
    };
    dibujarCentrado(cv, arte);
    esperarEspacio(dp, cv);

    caca_free_display(dp);
}

void PantallaCaca::mostrarDespedida() {
    caca_canvas_t* dp_raw = nullptr;
    caca_display_t* dp = caca_create_display(nullptr);
    if (!dp) return;
    caca_canvas_t* cv = caca_get_canvas(dp);

    caca_set_color_ansi(cv, CACA_LIGHTCYAN, CACA_BLACK);
    caca_clear_canvas(cv);

    // --- Dibujo de prueba de despedida ---
    std::vector<std::string> arte = {
        "  ____                 _                 ",
        " / ___| _ __ __ _  ___| |_   _ _ __ ___  ",
        "| |  _ | '__/ _` |/ __| | | | | '__/ _ \\ ",
        "| |_| || | | (_| | (__| | |_| | | |  __/ ",
        " \\____||_|  \\__,_|\\___|_|\\__,_|_|  \\___| ",
        "",
        "   Gracias por usar el simulador",
        "            Equipo 10"
    };
    dibujarCentrado(cv, arte);
    esperarEspacio(dp, cv);

    caca_free_display(dp);
}