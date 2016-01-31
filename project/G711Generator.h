/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

using namespace ns3;

#include "ns3/node.h"
#include "ns3/net-device.h"
#include "ns3/application.h"
#include "ns3/socket.h" 


class G711Generator : public Application
{
public:
  G711Generator ();
  
  void SetRemote(std::string socketType, Address remote,  uint16_t port);
  void SetRate (double rate);
  void SetSize (uint32_t size);

 

private:
  virtual void StartApplication (void){
      std::cout << "Arranco la aplicacion" << std::endl;

    // NS_LOG_INFO("Un nuevo generador de G711 comienza a transmitir");
    DoGenerate();
  }

  virtual void StopApplication (void){ //Hay que comprobar que se deje de transmitir, quizá haya que cancelar el próximo evento del Dogenerate
    // NS_LOG_INFO("Se detiene un generador de G711");    
    std::cout << "Termino la aplicacion. Paquetes enviados: "<< num_pkts << std::endl;
    Simulator::Cancel(m_next);


  }
  
  void DoGenerate (void);
  

  double        tbPkts;
  uint32_t      sizePkt;
  Ptr<Socket>   m_socket;
  EventId       m_next;
  
  uint32_t      num_pkts;
  

};