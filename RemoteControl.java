package ___LEDClient;

import java.awt.desktop.ScreenSleepEvent;

import org.eclipse.paho.client.mqttv3.*;

public class RemoteControl {
    
    private MqttClient client;
    private String clientId;

    public RemoteControl() {
        clientId = MqttClient.generateClientId();
        client = null;
    }
    
    public void publishMessage(String command) {
        try {
            if (client == null) {
                client = new MqttClient("tcp://broker.hivemq.com:1883", clientId);
            }
            if (!client.isConnected()) 
            {
                client.connect();
            }
            MqttMessage message = new MqttMessage();
            message.setPayload(command.getBytes());
            client.publish("testtopic/temp", message); // champ/iot the same TOPIC
            System.out.println("Message published");
        } catch (MqttException e) {
            e.printStackTrace();
        }
    }
    
    public void disconnect() {
        try {
            client.disconnect();
            System.out.println("Disconnected");
        } catch (MqttException e) {
            e.printStackTrace();
        }
    }
    
    public static void main(String[] args) throws InterruptedException {
        RemoteControl mqtt = new RemoteControl();
        
        while(true) 
        {
            mqtt.publishMessage("TurnOnLight");
            Thread.sleep(2000);
            mqtt.publishMessage("TurnOffLight");
            Thread.sleep(2000);
        
        }
    }

}
