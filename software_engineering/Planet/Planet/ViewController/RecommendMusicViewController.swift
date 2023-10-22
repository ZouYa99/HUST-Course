//
//  RecommendMusicViewController.swift
//  Planet
//
//  Created by ZouYa on 2021/12/20.
//

import UIKit

class RecommendMusicViewController: UIViewController {
    
    var homeBtn = UIButton()
    var musicArray:[Music] = []
    var cardArray:[CardView] = []
    var constraints:[NSLayoutConstraint]!
    
    var waitingLabel = UILabel()

    override func viewDidLoad() {
        super.viewDidLoad()
        self.view.backgroundColor = UIColor(red:36/255.0, green: 134/255.0, blue: 185/255.0, alpha: 1.0)
        // Do any additional setup after loading the view.
        setupHomeBtn()
        setupWaiting()
        getAllRecommendMusic()
        let swipe = UISwipeGestureRecognizer(target: self, action: #selector(swipe))
        self.view.addGestureRecognizer(swipe)
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
    
    @objc func swipe(){
        let curCons = constraints[0]
        curCons.constant = 500
        UIView.animate(withDuration: 2.0, delay: 0, usingSpringWithDamping: 0.75, initialSpringVelocity: 1, options: .curveEaseOut, animations: {
            self.view.layoutIfNeeded()
        }, completion: nil)
        constraints.remove(at: 0)
        cardArray.remove(at: 0)
    }
    
    private func getAllRecommendMusic(){
        //IP是119.3.154.207，端口是8080
        print("post")
        let webAPI = WebAPI(path: "http://119.3.154.207:8080/music/recommend", method: .post, parameter: nil)
        let user_id = UserDefaults.standard.string(forKey: "email")
        let response = NetworkMgr.shared.request(API: webAPI, parameters: ["user_id":user_id!], headers: nil)
        response.responseDict { [self] result in
            switch result {
            case .success(let model):
                print(model)
                let status = model["status"] as! Int
                if status == 1 {
                    let musics = model["Music"] as! Array<NSDictionary>
                    self.musicArray = []
                    for dic in musics{
                        let id = dic["MusicID"] as! Int
                        let name = dic["MusicName"] as! String
                        let sin = dic["Singer"] as! String
                        let cov = dic["Cover"] as! String
                        let ly = dic["Lyric"] as! String
                        let ty = dic["Type"] as! String
                        let cur = Music(MusicID: id, MusicName: name, Singer: sin, Cover: cov, Lyric: ly , _Type: ty)
                        self.musicArray.append(cur)
                    }
                    DispatchQueue.main.async {
                        cardArray = []
                        constraints = []
                        for music in self.musicArray {
                            self.setupCard(music: music)
                        }
                        constraints.reverse()
                        cardArray.reverse()
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
        constraints.append(constraint)
        cardView.isFavorite = false
        cardView.setup(title: music.MusicName, singer: music.Singer, lyrics: music.Lyric, cover: UIImage(named: "red")!,id:music.MusicID,coverStr: music.Cover,type: music._Type)
        cardView.isUserInteractionEnabled = true
        cardArray.append(cardView)
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
