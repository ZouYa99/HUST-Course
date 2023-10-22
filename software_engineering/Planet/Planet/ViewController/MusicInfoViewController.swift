//
//  MusicInfoViewController.swift
//  Planet
//
//  Created by ZouYa on 2021/12/22.
//

import UIKit

class MusicInfoViewController: UIViewController {
    
    var homeBtn = UIButton()
    var waitingLabel = UILabel()
    var card = CardView()

    override func viewDidLoad() {
        super.viewDidLoad()
        self.view.backgroundColor = UIColor(red:36/255.0, green: 134/255.0, blue: 185/255.0, alpha: 1.0)
        // Do any additional setup after loading the view.
        setupWaiting()
        setupHomeBtn()
    }
    
    private func setupWaiting(){
        self.view.addSubview(waitingLabel)
        waitingLabel.text = "Waiting..."
        waitingLabel.textColor = .white
        waitingLabel.font = UIFont.systemFont(ofSize: 35)
        waitingLabel.textAlignment = .center
        waitingLabel.backgroundColor = .clear
        waitingLabel.sizeToFit()
        waitingLabel.snp.makeConstraints { make in
            make.center.equalToSuperview()
        }
    }
    
    public func getInfo(id:Int){
        let webAPI = WebAPI(path: "http://119.3.154.207:8080/music/detail", method: .get, parameter: nil)
        print("getdetail")
        print(id)
        let response = NetworkMgr.shared.request(API: webAPI, parameters: ["music_id":id], headers: nil)
        response.responseDict { [self] result in
            switch result {
            case .success(let model):
                print(model)
                let status = model["status"] as! Int
                if status == 1 {
                    let dic = model["music"] as! Dictionary<String, Any>
                    let id = dic["MusicID"] as! Int
                    let name = dic["MusicName"] as! String
                    let sin = dic["Singer"] as! String
                    let cov = dic["Cover"] as! String
                    let ly = dic["Lyric"] as! String
                    let ty = dic["Type"] as! String
                    let cur = Music(MusicID: id, MusicName: name, Singer: sin, Cover: cov, Lyric: ly , _Type: ty)
                    DispatchQueue.main.async {
                        self.setupCard(music: cur)
                    }
                }else{
                    
                }
            case .failure(_):
                print("failure")
                break
            }
        }
    }
    
    private func setupCard(music:Music){
        let cardView = CardView(frame: CGRect(x: 10, y: 130, width: screen_width, height: screen_height))
        cardView.isFavorite = true
        self.view.addSubview(cardView)
        let image = UIImage(named: "card")
        let multiply = CGFloat(image!.size.height) / CGFloat(image!.size.width)
        cardView.snp.makeConstraints { make in
            make.top.equalToSuperview().offset(130)
            make.width.equalToSuperview().multipliedBy(0.78)
            make.height.equalTo(cardView.snp.width).multipliedBy(multiply)
        }
        let constraint = cardView.centerXAnchor.constraint(equalTo: self.view.centerXAnchor, constant: 0)
        constraint.isActive = true
        cardView.setup(title: music.MusicName, singer: music.Singer, lyrics: music.Lyric, cover: UIImage(named: "red")!,id:music.MusicID,coverStr: music.Cover,type: music._Type)
        cardView.isUserInteractionEnabled = true
    }
    
    private func setupHomeBtn(){
        self.view.addSubview(homeBtn)
        homeBtn.backgroundColor = UIColor(red:21/255.0, green: 85/255.0, blue: 154/255.0, alpha: 1.0)
        homeBtn.layer.masksToBounds = true
        homeBtn.layer.cornerRadius = 40
        homeBtn.layer.borderColor = CGColor.init(red: 199/255.0, green: 210/255.0, blue: 212/255.0, alpha: 1)
        homeBtn.layer.borderWidth = 8
        homeBtn.snp.makeConstraints { make in
            make.width.height.equalTo(80)
            make.bottom.equalToSuperview().offset(-100)
            make.centerX.equalToSuperview()
        }
        homeBtn.addTarget(self, action: #selector(goBack), for: .touchUpInside)
    }
    
    @objc func goBack(){
        //释放当前页面
        self.dismiss(animated: true)
    }

}
