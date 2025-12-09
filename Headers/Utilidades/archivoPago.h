#pragma once
#include "../../Headers/Persistence/ArchivoPagos.h"
#include "../../Headers/Entities/Pedido.h"

// Esta función sí devuelve bool porque retorna éxito o fallo
bool registrarPagoParaPedido(ArchivoPagos& archivoPagos, Pedido& pedido);


void mostrarPagoDePedido(ArchivoPagos& archivoPagos, int idPedido);
