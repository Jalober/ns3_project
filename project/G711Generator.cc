/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include <ns3/core-module.h>
#include <ns3/callback.h>
#include <ns3/packet.h>
#include "G711Generator.h"
#include "ns3/command-line.h"

using namespace ns3;



NS_LOG_COMPONENT_DEFINE ("G711");


G711Generator::G711Generator ()
{
	tbPkts = 0.02; //Por defecto son 50 pps
	sizePkt = 172; //Payload+RTP
	num_pkts = 0;
 
	NS_LOG_WARN("ESTA VERSION DE G711 NO SE PUEDE ENTREGAR. Falta revisar: \n - Comentarios \n - Longitud de lineas y tabulación \n - num_pkts y demás debugueo." );

}

void G711Generator::StartApplication (void) {
    NS_LOG_FUNCTION(this);

    // NS_LOG_INFO("Un nuevo generador de G711 comienza a transmitir");
    DoGenerate();
}

void G711Generator::StopApplication (void){ //Hay que comprobar que se deje de transmitir, quizá haya que cancelar el próximo evento del Dogenerate
    // NS_LOG_INFO("Se detiene un generador de G711");
    NS_LOG_FUNCTION(this);
    NS_LOG_INFO("Paquetes enviados: " << num_pkts);       
    Simulator::Cancel(m_next);

}


void 
G711Generator::SetRemote(std::string socketType, 
						Address remote,  uint16_t port)
{
 	TypeId tid = TypeId::LookupByName (socketType);
 	m_socket = Socket::CreateSocket (GetNode (), tid);
 	int err = m_socket->Bind ();
 	err += m_socket->ShutdownRecv ();
    err += m_socket->Connect (InetSocketAddress (Ipv4Address::ConvertFrom(remote), port));
        
    if(err != 0)
        NS_LOG_ERROR("Fallo de configuración en SetRemote de G711");
 
    
}


void 
G711Generator::SetRate (double rate)
{
	tbPkts = 1/rate;
}

void 
G711Generator::SetSize (uint32_t size)
{
	sizePkt = size;
}



void
G711Generator::DoGenerate (void)
{
    m_next = Simulator::Schedule (Seconds (tbPkts), 
                &G711Generator::DoGenerate, this);
                
    Ptr<Packet> p = Create<Packet> (sizePkt);
  
  
    int bytes = m_socket->Send (p) ;
    if(bytes >= 0)
        NS_LOG_LOGIC("Bytes enviados: " << bytes);
    else
        num_pkts++;
}
