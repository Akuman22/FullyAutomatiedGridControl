void coordinate_print()
{
  Serial.print("Start coordinates: (");
  Serial.print(xStart);
  Serial.print(",");
  Serial.print(yStart);
  Serial.print(") Destintion coordinates: (");
  Serial.print(xDestination);
  Serial.print(",");
  Serial.print(yDestination);
  Serial.println(")");
}
