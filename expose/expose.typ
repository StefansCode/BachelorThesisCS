= Exposé Bachelorarbeit Stefan Schulz

Deutscher Titel: DSP-Bibliotheksentwicklung angewandt als digitaler Synthesizer

Englischer Titel: DSP-Library Development applied as a Digital Synthesizer

Voraussichtlicher Beginn: April 2026

Gewünschte Gutachter:innen:

-  Erstgutachter: John Witulski

== Motivation

Digitale Signalverarbeitung wird wegen ihrer Flexibilität oft der 
analogen Signalverarbeitung bevorzugt. Für interessierte Anfänger können 
die existierenden Bibliotheken wie zum Beispiel die ESP-DSP Bibliothek
schnell zu komplex werden.

Dabei ist es eigentlich ganz einfach: „Signal geht rein, Signal geht raus“. 
Diese Einstellung wird von Java-Streams sehr schön umgesetzt und kann 
auch als DSP-Bibliothek umgesetzt werden.

Da Synthesizer nichts anderes machen als das Verarbeiten von Signalen
im menschlich hörbaren Frequenzbereich, lässt sich so eine schöne 
Beispielanwendung bauen.

In dieser Bachelorarbeit möchte ich die Entwicklung der Bibliothek 
dokumentieren und die Theorie der Signalverarbeitung anhand dieser 
erklären.

== Ziele

Entwicklung einer leicht anwendbaren und erweiterbaren
DSP-Bibliothek für den ESP32-S3,
basierend auf der in den ersten beiden Quellen erwähnten Signaltheorie.

Dabei möchte ich Signale als Objekte behandeln und diese mit einem 
Signalbuilder aus verschiedenen Quellen erstellen, bearbeiten und an
verschiedene Ausgänge senden. Signalbuilder stellen Verkettungen von 
Systemen dar, und sollen ähnlich zu Java-Streams als eine fluent API 
entwickelt werden.

Signalquellen können ADCs oder Oszillatoren, welche z.B. als Wavetable 
implementiert sind, sein.

Zur Bearbeitung der Signale möchte ich verschiedenste Filter 
(z.B. Tiefpass, Hochpass, Kerbfilter, Kammfilter, Glockenfilter) und 
Synthesizer-Effekte aus Quellen 5 und 6 (z.B. Verzerrung, Kompression, 
Delay, Phasor) implementieren.

Diese Bibliothek möchte ich mit einem ESP32-S3, einem DAC (Digital-Analog-Wandler),
ein paar Tastern und einem oder zwei Drehgebern (rotary encoder)
nutzen, um einen Synthesizer zu bauen.

== Mögliche Erweiterungen

- Visualisierung der Signale über einen OLED-Bildschirm
- Persistentes Speichern von bearbeiteten Signalen auf einer SD-Karte
- MIDI-Eingabe zum Steuern einzelner Komponenten
- Kompatibilität mit Arduino
- Einbinden der ESP-DSP Bibliothek

== grober Zeitplan

1. Monat: 
  - Einleitung ins Thema und den Prozess.
  - Aufbau der Hardware.
  - Erklärung und Implementierung der Softwarestruktur.

2. Monat: 
  - Implementierung von grundlegenden Komponenten.
  - Erklärung der Theorie hinter diesen Komponenten.
  - Die Bibliothek sollte nun nutzbar sein.

3. Monat: 
  - Fertig bauen des Synthesizers mit der Bibliothek und der Hardware.
  - Implementierung weiterer Komponenten
  - Überarbeitung der Bachelorarbeit

== Verwandte Arbeiten

1. ESP-DSP Bibliothek (offizielle und schnelle aber komplexe Bibliothek)
   - Link: https://docs.espressif.com/projects/esp-dsp/en/latest/esp32/index.html

2. Mozzi Arduino-Sound-Synthese-Bibliothek
   - https://sensorium.github.io/Mozzi/

== Quellen

1. Digitale Signalverarbeitung: mit einer Einführung in die kontinuierlichen Signale und Systeme 
   - Daniel Ch. von Grünigen ISBN: 978-3-446-41463-1

2. Digitale Signalverarbeitung: Filterung und Spektralanalyse mit MATLAB-Übungen
   - Karl-Dirk Kammeyer ISBN: 978-3-519-46122-7

3. Making Embedded Systems: Design Patterns for Great Software
   - Elecia White ISBN: 978-1-098-15154-6

4. DAFX: Digital Audio Effects
   - Udo Zölzer ISBN: 0-471-49078-4

5. https://www.sounddesign.uni-bonn.de/sound-design

6. THE ART OF VA FILTER DESIGN
   - Vadim Zavalishin 
   - Link: https://www.native-instruments.com/fileadmin/ni_media/downloads/pdf/VAFilterDesign_2.1.2.pdf
