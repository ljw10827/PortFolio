using System.Collections;
using System.Collections.Generic;
using UnityEngine;

//! 지역화 관리자
public class CLocalizeManager : CSingleton<CLocalizeManager> {
	private Dictionary<string, string> m_oStringList = null;

	//! 초기화
	public override void Awake() {
		base.Awake();
		m_oStringList = new Dictionary<string, string>();
	}

	//! 문자열을 반환한다
	public string GetStringForKey(string a_oKey) {
		if(m_oStringList.ContainsKey(a_oKey)) {
			return m_oStringList[a_oKey];
		}

		return a_oKey;
	}
	
	//! 문자열 리스트를 제거한다
	public void ResetStringList() {
		m_oStringList.Clear();
	}

	//! 문자열 리스트를 불러온다
	public void LoadStringListFromFile(string a_oFilepath) {
		this.ResetStringList();
		var oStringPairList = CSVParser.ParseFromResource(a_oFilepath);

		for(int i = 0; i < oStringPairList.Count; ++i) {
			var oStringPair = oStringPairList[i];

			string oKey = oStringPair["Key"];
			string oString = oStringPair["Value"];

			m_oStringList.Add(oKey, oString);
		}
	}
}
