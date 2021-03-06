import java.awt.*;
import java.awt.event.*;
import java.awt.datatransfer.*;
import javax.swing.*;
import java.io.*;


/* By FABIAN KOBER
 * This program is a Utility for working with the ArduinoBoy.
 * 
 * With it you can intuitively create Icons for programs in the ArduinoBoy OS.
 * 
 * Just draw with the LEFT MOUSE BUTTON, erase with the RIGHT MOUSE BUTTON, invert what you have drawn with the MIDDLE MOUSE BUTTON
 * and clear the canvas with SPACE.
 * 
 * Once you are happy with your icon press ENTER and the code that defines the icon is copied to your clipboard.
 * Now you can just paste it into the ArduinoBoy program and work with it
 */


final int WIDTH = 8;
final int HEIGHT = 8;
final int PIXEL_SIZE = 100;

byte[][] image = new byte[HEIGHT][WIDTH];

boolean leftMouseButtonHeld = false;
boolean rightMouseButtonHeld = false;

void setup() {
  size(800, 800);
}

void draw() {
  for (int rows = 0; rows < HEIGHT; ++rows) {
    for (int cols = 0; cols < WIDTH; ++cols) {
      float pixelPosX = cols*PIXEL_SIZE;
      float pixelPosY = rows*PIXEL_SIZE;

      if (leftMouseButtonHeld) {
        if (mouseX < pixelPosX + PIXEL_SIZE && mouseX > pixelPosX && mouseY < pixelPosY + PIXEL_SIZE && mouseY > pixelPosY) {
          image[rows][cols] = 1;
        }
      } else if (rightMouseButtonHeld) {
        if (mouseX < pixelPosX + PIXEL_SIZE && mouseX > pixelPosX && mouseY < pixelPosY + PIXEL_SIZE && mouseY > pixelPosY) {
          image[rows][cols] = 0;
        }
      }



      fill(map(image[rows][cols], 0, 1, 0, 255));
      stroke(255);
      rect(pixelPosX, pixelPosY, PIXEL_SIZE, PIXEL_SIZE);
    }
  }
}

void mousePressed() {
  switch(mouseButton) {
  case LEFT:
    leftMouseButtonHeld = true;
    break;
  case RIGHT:
    rightMouseButtonHeld = true;
    break;
  case CENTER:
    for (int rows = 0; rows < HEIGHT; ++rows) {
      for (int cols = 0; cols < WIDTH; ++cols) {
        image[rows][cols] = image[rows][cols] > 0 ? (byte)0 : (byte)1;
      }
    }
    break;
  }
}

void mouseReleased() {
  switch(mouseButton) {
  case LEFT:
    leftMouseButtonHeld = false;
    break;
  case RIGHT:
    rightMouseButtonHeld = false;
    break;
  }
}

void keyPressed() {
  if (key == ' ') {
    image = new byte[HEIGHT][WIDTH];
    return;
  } else if (keyCode == ENTER) {
    String part1 = "byte ic[HEIGHT] = ";

    String array = "{";
    for (int row = 0; row < HEIGHT; ++row) {
      int val = 0;
      for (int col = 0; col < WIDTH; ++col) {
        val += image[row][col] == 1 ? pow(2, col) : 0;
      }
      array += val;
      if (row < HEIGHT -1) {
        array += ",";
      }
    }

    array += "};";

    String output = part1 +array;
    println(output);

    StringSelection data = new StringSelection(output);
    Clipboard clipboard = 
      Toolkit.getDefaultToolkit().getSystemClipboard();
    clipboard.setContents(data, data);
  }
}