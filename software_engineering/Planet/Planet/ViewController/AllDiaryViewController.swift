//
//  AllDiaryViewController.swift
//  Planet
//
//  Created by ZouYa on 2021/12/21.
//

import UIKit

class AllDiaryViewController: UIViewController {
    
    var searchBar = UITextField()
    var confirmBtn = UIButton()
    var collectionView:UICollectionView!
    var layout = UICollectionViewFlowLayout()
    
    var numberOfDiaries:Int = 0
    var contents:[String] = []
    
    var homeBtn = UIButton()

    override func viewDidLoad() {
        super.viewDidLoad()
        self.view.backgroundColor = UIColor(red:36/255.0, green: 134/255.0, blue: 185/255.0, alpha: 1.0)
        // Do any additional setup after loading the view.
        setupHomeBtn()
        getAllDiaries()
        searchBar.delegate = self
        searchBar.returnKeyType = .done
        setupTextField()
    }
    
    private func setupTextField(){
        self.view.addSubview(searchBar)
        searchBar.textColor = .black
        searchBar.leftView = UIView(frame: CGRect(x: 0, y: 0, width: 8, height: 0))
        searchBar.leftViewMode = .always
        searchBar.layer.masksToBounds = true
        searchBar.layer.cornerRadius = 8
        searchBar.layer.borderColor = CGColor(red: 1, green: 1, blue: 1, alpha: 1)
        searchBar.layer.borderWidth = 3
        searchBar.backgroundColor = .clear
        searchBar.snp.makeConstraints { make in
            make.left.equalToSuperview().offset(30)
            make.top.equalToSuperview().offset(80)
            make.height.equalTo(50)
            make.width.equalTo(screen_width - 160)
        }
        
        self.view.addSubview(confirmBtn)
        confirmBtn.backgroundColor = .lightGray
        confirmBtn.setTitle("确认", for: .normal)
        confirmBtn.setTitleColor(.black, for: .normal)
        confirmBtn.layer.masksToBounds = true
        confirmBtn.layer.cornerRadius = 10
        confirmBtn.snp.makeConstraints { make in
            make.left.equalTo(searchBar.snp.right).offset(20)
            make.top.equalTo(searchBar.snp.top)
            make.height.equalTo(50)
            make.width.equalTo(80)
        }
        confirmBtn.addTarget(self, action: #selector(searchForTag), for: .touchUpInside)
        confirmBtn.isUserInteractionEnabled = false
    }
    
    @objc func searchForTag(){
        //IP是119.3.154.207，端口是8080
        let webAPI = WebAPI(path: "http://119.3.154.207:8080/diary/tag", method: .get, parameter: nil)
        let user_id = UserDefaults.standard.string(forKey: "email")
        let response = NetworkMgr.shared.request(API: webAPI, parameters: ["user_id":user_id!,"tag":searchBar.text!], headers: nil)
        response.responseDict { result in
            switch result {
            case .success(let model):
                print(model)
                let status = model["status"] as! Int
                if status == 1 {
                    let diaries = model["diaries"] as! Array<NSDictionary>
                    self.numberOfDiaries = diaries.count
                    self.contents = []
                    for dic in diaries {
                        self.contents.append(dic["content"] as! String)
                    }
                    DispatchQueue.main.async {
                        self.collectionView.reloadData()
                    }
                }else{
                    DispatchQueue.main.async {
                        self.presentAlert(isTag: true)
                    }
                }
            case .failure(_):
                DispatchQueue.main.async {
                    self.presentAlert(isTag: true)
                }
                break
            }
        }
    }
    
    private func getAllDiaries(){
        //IP是119.3.154.207，端口是8080
        let webAPI = WebAPI(path: "http://119.3.154.207:8080/diary/", method: .get, parameter: nil)
        let user_id = UserDefaults.standard.string(forKey: "email")
        let response = NetworkMgr.shared.request(API: webAPI, parameters: ["user_id":user_id!], headers: nil)
        response.responseDict { result in
            switch result {
            case .success(let model):
                let status = model["status"] as! Int
                if status == 1 {
                    let diaries = model["diaries"] as! Array<NSDictionary>
                    self.numberOfDiaries = diaries.count
                    for dic in diaries {
                        self.contents.append(dic["content"] as! String)
                    }
                    DispatchQueue.main.async {
                        self.setupCollectionView()
                    }
                }else{
                    DispatchQueue.main.async {
                        self.presentAlert(isTag: false)
                    }
                }
            case .failure(_):
                DispatchQueue.main.async {
                    self.presentAlert(isTag: false)
                }
                break
            }
        }
    }
    
    private func presentAlert(isTag:Bool){
        var msg:String
        if isTag {
            msg = "没找到这个tag下的日记哦"
        }else{
            msg = "获取失败，还没写过日记喔"
        }
        let alertView = UIAlertController.init(title: "提示", message: msg, preferredStyle: .alert)
        let alert = UIAlertAction.init(title: "确定", style: .default) { (UIAlertAction) in
            if !isTag {
                self.dismiss(animated: true, completion: nil)
            }
        }
        alertView.addAction(alert)
        self.present(alertView, animated: true, completion: nil)
    }
    
    private func setupCollectionView(){
        layout.scrollDirection = .vertical
        layout.estimatedItemSize = CGSize(width: screen_width, height: 100)
        
        collectionView = UICollectionView(frame: CGRect(x: 0, y: 150, width: screen_width, height: 510), collectionViewLayout: layout)
        self.view.addSubview(collectionView)
        collectionView.alwaysBounceVertical = true
        collectionView.autoresizingMask = [.flexibleWidth, .flexibleHeight]
        collectionView.delegate = self
        collectionView.dataSource = self
        collectionView.register(DiaryCollectionCell.self, forCellWithReuseIdentifier: DiaryCollectionCell.identifier)
        collectionView.backgroundColor = .clear
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
    
    override func touchesBegan(_ touches: Set<UITouch>, with event: UIEvent?) {
        searchBar.resignFirstResponder()
    }
    
}

extension AllDiaryViewController:UICollectionViewDelegate,UICollectionViewDataSource{
    
    func collectionView(_ collectionView: UICollectionView, numberOfItemsInSection section: Int) -> Int {
        return numberOfDiaries
    }
    
    func collectionView(_ collectionView: UICollectionView, cellForItemAt indexPath: IndexPath) -> UICollectionViewCell {
        let cell = collectionView.dequeueReusableCell(withReuseIdentifier: DiaryCollectionCell.identifier, for: indexPath) as! DiaryCollectionCell
        cell.setupUI(text: contents[indexPath.item])
        return cell
    }
    
}

extension AllDiaryViewController:UITextFieldDelegate{
    func textFieldShouldReturn(_ textField: UITextField) -> Bool {
        textField.resignFirstResponder()
        return true
    }
    
    func textFieldDidEndEditing(_ textField: UITextField) {
        if searchBar.text?.count != 0 {
            confirmBtn.backgroundColor = UIColor(red: 231/255.0, green: 124/255.0, blue: 142/255.0, alpha: 1)
            confirmBtn.isUserInteractionEnabled = true
        }else{
            confirmBtn.backgroundColor = .lightGray
            confirmBtn.isUserInteractionEnabled = false
        }
    }
}

extension AllDiaryViewController:UICollectionViewDelegateFlowLayout{
    
    func collectionView(_ collectionView: UICollectionView, layout collectionViewLayout: UICollectionViewLayout, sizeForItemAt indexPath: IndexPath) -> CGSize {
        
        let cell = DiaryCollectionCell()
        cell.setupUI(text: contents[indexPath.item])
        return cell.returnSize()
        
    }
    
    func collectionView(_ collectionView: UICollectionView, layout collectionViewLayout: UICollectionViewLayout, minimumLineSpacingForSectionAt section: Int) -> CGFloat {
        return 10
    }
    
    func collectionView(_ collectionView: UICollectionView, layout collectionViewLayout: UICollectionViewLayout, minimumInteritemSpacingForSectionAt section: Int) -> CGFloat {
        return 10
    }
    
}
