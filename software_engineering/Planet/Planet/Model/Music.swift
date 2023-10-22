//
//  Music.swift
//  Planet
//
//  Created by ZouYa on 2021/12/22.
//

import Foundation

struct Music:Codable{
    var MusicID:Int
    var MusicName:String
    var Singer:String
    var Cover:String
    var Lyric:String
    var _Type:String
}


struct PostMusic:Codable{
    var user_id:String
    var music:Music
}

struct DeleteMusic:Codable{
    var user_id:String
    var music_code:Int
}

struct FavoriteMusic:Codable{
    var music_name:String
    var music_id:Int
}
