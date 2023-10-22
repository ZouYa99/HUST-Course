//
//  Diary.swift
//  Planet
//
//  Created by ZouYa on 2021/12/21.
//

import Foundation
struct Diary:Codable{
    var user_id:String
    struct diary_struct:Codable{
        var user_id:String
        var create_at:String = ""
        var diary_code:String = ""
        var hash_tag:String
        var content:String
    }
    var diary:diary_struct
}
