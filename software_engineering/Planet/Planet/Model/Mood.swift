//
//  Mood.swift
//  Planet
//
//  Created by ZouYa on 2021/12/20.
//

import Foundation

struct Emotion:Codable{
    var user_id:String
    var emotions:[String]
}

//var mood:Mood = .glad
//switch(btn.title(for: .normal)){
//case "美滋滋":mood = .glad
//case "裂开":mood = .split
//case "等天晴":mood = .waitingForSunny
//case "发呆":mood = .daze
//case "emo":mood = .emo
//case "元气满满":mood = .positive
//case "沉迷学习":mood = .study
//case "摸鱼":mood = .messAround
//case .none:
//    break
//case .some(_):
//    break
//}
//moodArray.append(mood)

enum Mood:Int{
    case glad = 1
    case split
    case waitingForSunny
    case daze
    case emo
    case positive
    case study
    case messAround
}
