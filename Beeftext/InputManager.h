/// \file
/// \author Xavier Michelon
///
/// \brief Declaration of input manager
///  
/// Copyright (c) Xavier Michelon. All rights reserved.  
/// Licensed under the MIT License. See LICENSE file in the project root for full license information.  


#ifndef BEEFTEXT_INPUT_MANAGER_H
#define BEEFTEXT_INPUT_MANAGER_H


//**********************************************************************************************************************
/// \brief An input manager capture input by keyboard and mouse and process the events 
//**********************************************************************************************************************
class InputManager : public QObject
{
   Q_OBJECT
public: // data types
   enum { 
      KeyboardStateSize = 256, ///< The size of the keyboard state array
   }; 
   struct KeyStroke {
      quint32 virtualKey; ///< The virtual keyCode
      quint32 scanCode; ///< The scanCode
      quint8 keyboardState[KeyboardStateSize]; ///< The state of the keyboard at the moment the keystroke occurred
   };
public: // static member functions
   static InputManager& instance(); ///< Return the only allowed instance of the class

public: // member functions
   InputManager(InputManager const&) = delete; ///< Disabled copy constructor
   InputManager(InputManager&&) = delete; ///< Disabled move constructor
   ~InputManager(); ///< Default destructor
   InputManager& operator=(InputManager const&) = delete; ///< Disabled assignment operator
   InputManager& operator=(InputManager&&) = delete; ///< Disabled move assignment operator
   bool isKeyboardHookEnable() const; ///< Is the keyboard hook enabled
   void enableKeyboardHook(); ///< Enable the keyboard hook
   void disableKeyboardHook(); ///< Disable the keyboard hook
   bool setKeyboardHookEnabled(bool enabled); ///< Enable or disable the keyboard hook
   bool isMouseHookEnabled() const; ///< Is the mouse hook enabled
   void enableMouseHook(); ///< Enable the mouse hook
   void disableMouseHook(); ///< Disable the mouse hook
   bool setMouseHookEnabled(bool enabled); ///< Enable or disable the keyboard hook

signals:
   void comboBreakerTyped(); ///< Signal for combo breaking events
   void characterTyped(QChar c); ///< Signal for character typed
   void backspaceTyped(); ///< Signal for backspace typed
   void substitutionShortcutTriggered();  ///< Signal emitted when the manual substitution shortcut is triggered

private: // member functions
   InputManager(); ///< Default constructor
   bool onKeyboardEvent(KeyStroke const& keyStroke); ///< The callback function called at every key event
   QString processKey(KeyStroke const& keyStroke, bool& outIsDeadKey); ///< Process a key stroke and return the generated characters 
   void onMouseClickEvent(int, WPARAM, LPARAM); ///< Process a mouse click event

private: // static member functions
   static LRESULT CALLBACK keyboardProcedure(int nCode, WPARAM wParam, LPARAM lParam); ///< The keyboard event callback
   static LRESULT CALLBACK mouseProcedure(int nCode, WPARAM wParam, LPARAM lParam); ///< The mouse event callback

private: // data members
   HHOOK keyboardHook_; ///< The handle to the keyboard hook used to be notified of keyboard events
   HHOOK mouseHook_; ///< The handle to the mouse hook used to be notified of mouse event
   KeyStroke deadKey_; ///< The currently active dead key
};




#endif // #ifndef TEXT__WATCH__INPUT__MANAGER__H