using System.Collections;
using System.Collections.Generic;
using UnityEngine;

//! 유틸리티 상수
public static partial class KDefine
{
	// 씬 관리자
	public static readonly string NAME_UI_CAMERA = "UI Camera";
	public static readonly string NAME_MAIN_CAMERA = "Main Camera";
	public static readonly string NAME_SCENE_MANAGER = "SceneManager";

	#if NGUI
	public static readonly string NAME_UI_ROOT = "UIs";
	#else
	public static readonly string NAME_UI_ROOT = "Canvas";
	#endif			// #if NGUI

	public static readonly string NAME_OBJECT_ROOT = "Object Root";

	// 사운드 관리자
	public static readonly int MAX_NUM_DUPLICATE_EFFECT_SOUND = 5;

	
}
