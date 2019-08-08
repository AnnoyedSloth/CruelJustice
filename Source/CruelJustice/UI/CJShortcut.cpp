// Fill out your copyright notice in the Description page of Project Settings.

#include "CJShortcut.h"
#include "Controller/CJPlayerController.h"
#include "UI/CJSkillWidget.h"

void UCJShortcut::NativeConstruct()
{
	Super::NativeConstruct();

	shortcuts.Add(Cast<UCJSkillWidget>(GetWidgetFromName("Shortcut1")));
	shortcuts.Add(Cast<UCJSkillWidget>(GetWidgetFromName("Shortcut2")));
	shortcuts.Add(Cast<UCJSkillWidget>(GetWidgetFromName("Shortcut3")));
	shortcuts.Add(Cast<UCJSkillWidget>(GetWidgetFromName("Shortcut4")));
	shortcuts.Add(Cast<UCJSkillWidget>(GetWidgetFromName("Shortcut5")));

}

void UCJShortcut::UseShortcut(int32 shortcutNum)
{
	if (shortcuts[shortcutNum - 1])
	{
		shortcuts[shortcutNum - 1]->Play();
	}
}

