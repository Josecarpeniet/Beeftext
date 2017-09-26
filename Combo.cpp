/// \file
/// \author Xavier Michelon
///
/// \brief Implementation of Combo class that associate a combo text and its substitution text
///  
/// Copyright (c) Xavier Michelon. All rights reserved.  
/// Licensed under the MIT License. See LICENSE file in the project root for full license information.  


#include "stdafx.h"
#include "Combo.h"
#include <XMiLib/SystemUtils.h>


using namespace xmilib;


//**********************************************************************************************************************
/// \param[in] comboText The combo text
/// \param[in] substitutionText The text that will replace the combo
//**********************************************************************************************************************
Combo::Combo(QString const& comboText, QString const& substitutionText)
   : comboText_(comboText)
   , substitutionText_(substitutionText)
{

}


//**********************************************************************************************************************
/// \return The combo text
//**********************************************************************************************************************
QString Combo::comboText() const
{
   return comboText_;
}


//**********************************************************************************************************************
/// \param[in] comboText The combo text
//**********************************************************************************************************************
void Combo::setComboText(QString const& comboText)
{
   comboText_ = comboText;
}


//**********************************************************************************************************************
/// \return The substitution text
//**********************************************************************************************************************
QString Combo::substitutionText() const
{
   return substitutionText_;
}


//**********************************************************************************************************************
/// \param[in] substitutionText the substitution text
//**********************************************************************************************************************
void Combo::setSubstitutionText(QString const& substitutionText)
{
   substitutionText_ = substitutionText;
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void Combo::performSubstitution()
{
   // select the typed combo by pressing Shift + Left n times (n being the number of characters in the combo)
   synthesizeKeystroke(VK_LSHIFT, true);
   for (qint32 i = 0; i < comboText_.size(); ++i)
   {
      synthesizeKeystroke(VK_LEFT, true);
      synthesizeKeystroke(VK_LEFT, false);
   }
   synthesizeKeystroke(VK_LSHIFT, false);

   // put the substitution text in the clipboard
   qApp->clipboard()->setText(substitutionText_);

   // send a paste command (Ctrl+V)
   synthesizeKeystroke(VK_LCONTROL, true);
   synthesizeKeystroke('V', true);
   synthesizeKeystroke('V', false);
   synthesizeKeystroke(VK_LCONTROL, false);
}
