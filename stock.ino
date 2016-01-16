//  // Check if a client has connected
//  WiFiClient client = server.available();
//  if (!client) {
//    analogWrite(5, 0);
//    analogWrite(4, 0);
//    digitalWrite(0, 1);
//    digitalWrite(2, 1);
//    return;
//  }
//  
//  // Wait until the client sends some data
//  Serial.println("new client");
//  while(!client.available()){
//    delay(1);
//  }
//  
//  // Read the first line of the request
//  String req = client.readStringUntil('\r');
//  Serial.println(req);
//  client.flush();
//  
//  // Match the request
//  int motorASpeed = 1023;
//  int motorBSpeed = 1023;
//  int motorAForward = 1;
//  int motorBForward = 1;
//  if (req.indexOf("/engines/") != -1) {
//    String parameters = req.substring(13);
//    int separatorPos = parameters.indexOf(",");
//    int httpPos = parameters.indexOf(" HTTP");
//    String leftText = parameters.substring(0,separatorPos);
//    String rightText = parameters.substring(separatorPos + 1, httpPos);
//
//    Serial.println("[" + leftText +"][" + rightText + "]");
//    int left = leftText.toInt();
//    int right = rightText.toInt();
//    if (left < 0) {
//      motorAForward = 0;
//    } else {
//      motorAForward = 1;
//    }
//    if (right < 0) {
//      motorBForward = 0;
//    } else {
//      motorBForward = 1;
//    }    
//    analogWrite(5, abs(left));
//    analogWrite(4, abs(right));
//    digitalWrite(0, motorAForward);
//    digitalWrite(2, motorBForward);
//  } else if (req.indexOf("/index.html") != - 1 || req.indexOf("/") != - 1) {
//    client.print("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n");
//    client.print("<html><head>");
//    client.print("</head><body>");
//    client.print("<script type='text/javascript' src='http://www.squix.org/blog/smartcar.js'></script>");
//    client.print("<a href='#' onclick='move(\"f\");'>forward</a><BR/>");
//    client.print("<a href='#' onclick='move(\"b\");'>backwards</a><BR/>");
//    client.print("<a href='#' onclick='move(\"l\");'>left</a><BR/>");
//    client.print("<a href='#' onclick='move(\"r\");'>right</a><BR/>");
//    client.print("<div id=\"dmEvent\"/>");
//    client.print("<div id=\"vector\"/>");
//    client.print("</body></html>");
//    analogWrite(5, 0);
//    analogWrite(4, 0);
//    digitalWrite(0, 1);
//    digitalWrite(2, 1);
//    return;
//  } 
//
//  
//  client.flush();
//
//  // Prepare the response
//  String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\nGPIO is now ";
//  s += "</html>\n";
//
//  // Send the response to the client
//  client.print(s);
//  delay(1);
//  Serial.println("Client disonnected");
//  delay(200);
//  // The client will actually be disconnected 
//  // when the function returns and 'client' object is detroyed
