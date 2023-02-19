// java script cyclic

if (Esp.getKey(0)) {
    Esp.setLed(0, "#FF0000");
}
else {
    Esp.setLed(0, "off");
}

if (toggle) {
    toggle = false;
    Esp.setLed(3, "#200000");
} else {
    toggle = true;
    Esp.setLed(3, "#001000");
}

if (Mqtt.connected()) {
    Mqtt.publish("x_cyc", x);
    Mqtt.publish("y_cyc", y);
    y++;

    //send job on every edge of key 0
    if (Esp.getKey(0) != oldKey) {
        x = x + 1;
        print("++x:" + x);

        Mqtt.publish("x", x);
        //Mqtt.publish("job","job:"+x);
        Mqtt.publish("ruth", "ruth:" + x);
    }
    oldKey = Esp.getKey(0);

    //print("ruth: "+ Mqtt.subscribe("ruth"));
    job = Mqtt.subscribe("job");
    print("job: " + job);

    print("x: " + Mqtt.subscribe("x"));
}