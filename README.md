# MATCH!: 2 Player Game with Infrared Communication

## Collaborators: Wannes Baes

## Context in which the project has been done:
 This project was created for the course Engineering Project in the Bachelor of Science in Engineering (Computer Science Engineering), under the supervision of Francis Wyffels, Tom Neutens, Thomas Lips, and Victor-Louis de Gusseme.

## General overview

MATCH! is a multiplayer game designed for two players using microcontrollers which communicate with infrared signals. Each player operates their own Dwenguino board. The objective is to guess which avatar the opponent has selected.

**How It Works:**

1. **Setup**: The game utilizes infrared (IR) communication to enable the two microcontrollers to send and receive signals.
2. **Gameplay**:
   - Players start at a menu and select a game type.
   - Each player secretly chooses an avatar.
   - Players take turns sending guesses about each other's avatars using IR signals.
3. **Signal Transmission**:
   - An IR LED on one board sends signals, while an IR sensor on the other receives them.
   - The signals encode guesses as binary data (0s and 1s) using pulse width modulation.
4. **Game States**: The game operates through defined states, with actions determined by the current state (e.g., menu, guessing).
5. **Winning**: The game reveals the winner after a set number of rounds based on correct guesses.
