//
//  FavoriteMusicViewController.swift
//  Planet
//
//  Created by ZouYa on 2021/12/20.
//

import UIKit

class FavoriteMusicViewController: UIViewController {
    
    var profile = UIImageView()
    var titleLabel = UILabel()
    var nickname = UILabel()
    
    var tableView = UITableView()
    var homeBtn = UIButton()
    
    var musicArray:[FavoriteMusic] = []

    override func viewDidLoad() {
        super.viewDidLoad()
        self.view.backgroundColor = UIColor(red:36/255.0, green: 134/255.0, blue: 185/255.0, alpha: 1.0)
        // Do any additional setup after loading the view.
        setupHomeBtn()
        setupProfile()
        setupLabel()
        getAllFavorite()
    }
    
    private func getAllFavorite(){
        //IP是119.3.154.207，端口是8080
        let webAPI = WebAPI(path: "http://119.3.154.207:8080/music/", method: .get, parameter: nil)
        let user_id = UserDefaults.standard.string(forKey: "email")
        let response = NetworkMgr.shared.request(API: webAPI, parameters: ["user_id":user_id!], headers: nil)
        response.responseDict { [self] result in
            switch result {
            case .success(let model):
                print(model)
                let status = model["status"] as! Int
                if status == 1 {
                    let musics = model["music"] as! Array<NSDictionary>
                    musicArray = []
                    for music in musics {
                        let id = music["music_id"] as! Int
                        let name = music["music_name"] as! String
                        let fMusic = FavoriteMusic(music_name: name, music_id: id)
                        musicArray.append(fMusic)
                    }
                    DispatchQueue.main.async {
                        self.setupTableView()
                    }
                }else{
                    
                }
            case .failure(_):
                print("failure")
                break
            }
        }
    }
    
    private func setupProfile(){
        let data = UserDefaults.standard.data(forKey: "profile")
        let image = UIImage(data: data!)!
        profile.image = image
        self.view.addSubview(profile)
        profile.layer.masksToBounds = true
        profile.layer.cornerRadius = 18
        profile.snp.makeConstraints { make in
            make.top.equalToSuperview().offset(80)
            make.left.equalToSuperview().offset(40)
            make.height.width.equalTo(120)
        }
    }
    
    private func setupLabel(){
        self.view.addSubview(titleLabel)
        titleLabel.text = "我喜欢的音乐"
        titleLabel.font = UIFont.systemFont(ofSize: 28)
        titleLabel.textColor = .white
        titleLabel.textAlignment = .left
        titleLabel.backgroundColor = .clear
        titleLabel.sizeToFit()
        titleLabel.snp.makeConstraints { make in
            make.left.equalTo(profile.snp.right).offset(30)
            make.top.equalTo(profile.snp.top).offset(10)
        }
        
        self.view.addSubview(nickname)
        nickname.text = UserDefaults.standard.string(forKey: "userName")
        nickname.textColor = .white
        nickname.font = UIFont.systemFont(ofSize: 20)
        nickname.textColor = .white
        nickname.textAlignment = .left
        nickname.backgroundColor = .clear
        nickname.sizeToFit()
        nickname.snp.makeConstraints { make in
            make.top.equalTo(titleLabel.snp.bottom).offset(20)
            make.left.equalTo(titleLabel.snp.left)
        }
    }
    
    private func setupTableView() {
        view.addSubview(tableView)
        tableView.backgroundColor = .clear
        tableView.layer.cornerRadius = 10
        tableView.layer.masksToBounds = true
        tableView.rowHeight = 60//行高
        tableView.register(MusicTableCell.self, forCellReuseIdentifier: MusicTableCell.identifier)
        
        tableView.delegate = self
        tableView.dataSource = self
        
        tableView.separatorStyle = .singleLine
        
        tableView.snp.makeConstraints { make in
            make.top.equalTo(profile.snp.bottom).offset(30)
            make.width.equalToSuperview().multipliedBy(0.90)
            make.height.equalToSuperview().multipliedBy(0.50)
            make.centerX.equalToSuperview()
        }
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

extension FavoriteMusicViewController:UITableViewDelegate,UITableViewDataSource{
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return musicArray.count
    }
    
    
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCell(withIdentifier: MusicTableCell.identifier) as! MusicTableCell
        cell.contentView.frame = CGRect(x: 0, y: 0, width: cell.contentView.frame.width, height: self.tableView.rowHeight)
        cell.setupLabel(text: musicArray[indexPath.row].music_name)
        
        return cell
    }
    
    func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        let vc = MusicInfoViewController()
        print(musicArray[indexPath.row].music_id)
        vc.getInfo(id:musicArray[indexPath.row].music_id)
        vc.modalPresentationStyle = .fullScreen
        self.present(vc, animated: true, completion: nil)
        tableView.deselectRow(at: indexPath, animated: true)
    }
    
    func tableView(_ tableView: UITableView, canEditRowAt indexPath: IndexPath) -> Bool {
        //cell是否可编辑
        return true
    }
    
    func tableView(_ tableView: UITableView, trailingSwipeActionsConfigurationForRowAt indexPath: IndexPath) -> UISwipeActionsConfiguration? {
        //cell 右划的时候 执行函数
        let delete = deleteAction(at: indexPath)
        return UISwipeActionsConfiguration(actions: [delete])
    }
    
    func deleteAction(at indexPath: IndexPath) -> UIContextualAction{
        //自定义的delete函数
        let action = UIContextualAction(style: .destructive, title: "删除") { (action, view, nil) in
            self.musicArray.remove(at: indexPath.row)//删掉数据
            self.tableView.deleteRows(at: [indexPath], with: .automatic)//删掉这一行
        }
        action.backgroundColor = .red
        return action
    }
}
