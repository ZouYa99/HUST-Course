//
//  RegisterViewController.swift
//  Planet
//
//  Created by ZouYa on 2021/12/19.
//

import UIKit
import SnapKit

class RegisterViewController: UIViewController {
    
    var homeBtn = UIButton()
    
    var pictureBtn = UIButton()
    var imagePicker = UIImagePickerController()
    
    var nameField = UITextField()
    var emailField = UITextField()
    var passwordField = UITextField()
    var verificationField = UITextField()
    
    var confirmBtn = UIButton()
    
    override func viewDidLoad() {
        super.viewDidLoad()

        // Do any additional setup after loading the view.
        self.view.backgroundColor = UIColor(red:36/255.0, green: 134/255.0, blue: 185/255.0, alpha: 1.0)
        setupHomeBtn()
        setupPictureBtn()
        setupTextField()
        
        imagePicker.delegate = self
        nameField.delegate = self
        emailField.delegate = self
        passwordField.delegate = self
        verificationField.delegate = self
        nameField.returnKeyType = .done
        emailField.returnKeyType = .done
        passwordField.returnKeyType = .done
        verificationField.returnKeyType = .done
    }
    
    private func setupTextField(){
        let attributes:[NSAttributedString.Key:Any] = [.foregroundColor: UIColor.darkGray]
        
        let attributedString4 = NSMutableAttributedString(string: "请输入用户名", attributes: attributes)
        self.view.addSubview(nameField)
        nameField.attributedPlaceholder = attributedString4
        nameField.backgroundColor = .white
        nameField.textColor = .black
        nameField.leftView = UIView(frame: CGRect(x: 0, y: 0, width: 8, height: 0))
        nameField.leftViewMode = .always
        nameField.layer.masksToBounds = true
        nameField.layer.cornerRadius = 10
        nameField.snp.makeConstraints { make in
            make.top.equalTo(pictureBtn.snp.bottom).offset(30)
            make.left.equalToSuperview().offset(50)
            make.width.equalTo(300)
            make.height.equalTo(60)
        }
        
        let attributedString1 = NSMutableAttributedString(string: "请输入邮箱", attributes: attributes)
        self.view.addSubview(emailField)
        emailField.attributedPlaceholder = attributedString1
        emailField.backgroundColor = .white
        emailField.leftView = UIView(frame: CGRect(x: 0, y: 0, width: 8, height: 0))
        emailField.textColor = .black
        emailField.leftViewMode = .always
        emailField.layer.masksToBounds = true
        emailField.layer.cornerRadius = 10
        emailField.snp.makeConstraints { make in
            make.top.equalTo(nameField.snp.bottom).offset(20)
            make.left.equalToSuperview().offset(50)
            make.width.equalTo(300)
            make.height.equalTo(60)
        }
        
        self.view.addSubview(passwordField)
        let attributedString2 = NSMutableAttributedString(string: "请输入新密码", attributes: attributes)
        passwordField.attributedPlaceholder = attributedString2
        passwordField.backgroundColor = .white
        passwordField.leftView = UIView(frame: CGRect(x: 0, y: 0, width: 8, height: 0))
        passwordField.textColor = .black
        passwordField.leftViewMode = .always
        passwordField.layer.masksToBounds = true
        passwordField.layer.cornerRadius = 10
        passwordField.isSecureTextEntry = true
        passwordField.snp.makeConstraints { make in
            make.top.equalTo(emailField.snp.bottom).offset(20)
            make.left.equalToSuperview().offset(50)
            make.width.equalTo(300)
            make.height.equalTo(60)
        }
        
        self.view.addSubview(verificationField)
        verificationField.backgroundColor = .white
        let attributedString3 = NSMutableAttributedString(string: "再次输入密码", attributes: attributes)
        verificationField.attributedPlaceholder = attributedString3
        verificationField.leftView = UIView(frame: CGRect(x: 0, y: 0, width: 8, height: 0))
        verificationField.isSecureTextEntry = true
        verificationField.leftViewMode = .always
        verificationField.textColor = .black
        verificationField.layer.masksToBounds = true
        verificationField.layer.cornerRadius = 10
        verificationField.snp.makeConstraints { make in
            make.top.equalTo(passwordField.snp.bottom).offset(20)
            make.left.equalToSuperview().offset(50)
            make.width.equalTo(300)
            make.height.equalTo(60)
        }
        
        self.view.addSubview(confirmBtn)
        confirmBtn.backgroundColor = .lightGray
        confirmBtn.setTitle("确认", for: .normal)
        confirmBtn.setTitleColor(.black, for: .normal)
        confirmBtn.layer.masksToBounds = true
        confirmBtn.layer.cornerRadius = 10
        confirmBtn.snp.makeConstraints { make in
            make.top.equalTo(verificationField.snp.bottom).offset(30)
            make.centerX.equalToSuperview()
            make.width.equalTo(120)
            make.height.equalTo(50)
        }
        confirmBtn.isUserInteractionEnabled = false
        confirmBtn.addTarget(self, action: #selector(confirmToPost), for: .touchUpInside)
    }
    
    @objc func confirmToPost(){
        //IP是119.3.154.207，端口是8080
        print("post")
        let webAPI = WebAPI(path: "http://119.3.154.207:8080/login/register", method: .post, parameter: nil)
        let response = NetworkMgr.shared.request(API: webAPI, parameters: ["email":emailField.text,"password":passwordField.text,"user_name":nameField.text], headers: nil)
        response.responseDict { result in
            switch result {
            case .success(let model):
                let status = model["status"] as! Int
                if status == 1 {
                    let msg = model["msg"] as! [String:String]
                    let userName = msg["user_name"]!
                    let email = msg["email"]!
                    //let password = model["password"]
                    UserDefaults.standard.set(userName, forKey: "userName")
                    UserDefaults.standard.set(email, forKey: "email")
                    DispatchQueue.main.async {
                        self.presentRegisterSuccessful(flag: true)
                    }
                }else{
                    DispatchQueue.main.async {
                        self.presentRegisterSuccessful(flag: false)
                    }
                }
            case .failure(_):
                DispatchQueue.main.async {
                    self.presentRegisterSuccessful(flag: false)
                }
                break
            }
        }
    }
    
    private func saveImageAsProfile(){
        let imageData = pictureBtn.imageView!.image!.pngData()
        UserDefaults.standard.set(imageData, forKey: "profile")
    }
    
    private func presentRegisterSuccessful(flag:Bool){
        let msg:String
        if flag {
            msg = "注册成功！快去登录叭"
        }else{
            msg = "不小心失败了，再试试吧"
        }
        let alertView = UIAlertController.init(title: "提示", message: msg, preferredStyle: .alert)
        let alert = UIAlertAction.init(title: "确定", style: .default) { (UIAlertAction) in
            self.saveImageAsProfile()
            self.dismiss(animated: true)
        }
        alertView.addAction(alert)
        self.present(alertView, animated: true, completion: nil)
    }
    
    private func setupPictureBtn(){
        view.addSubview(pictureBtn)
        
        pictureBtn.setImage(UIImage(named: "user"), for: UIControl.State.normal)
        pictureBtn.layer.masksToBounds = true
        pictureBtn.layer.cornerRadius = 50
        pictureBtn.snp.makeConstraints { make in
            make.centerX.equalToSuperview()
            make.top.equalToSuperview().offset(130)
            make.width.height.equalTo(100)
        }
        pictureBtn.addTarget(self, action: #selector(self.click(_:)), for: .touchDown)
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
        nameField.resignFirstResponder()
        emailField.resignFirstResponder()
        passwordField.resignFirstResponder()
        verificationField.resignFirstResponder()
    }

}

extension RegisterViewController:UITextFieldDelegate{
    func textFieldDidEndEditing(_ textField: UITextField) {
        if (emailField.text?.count != 0)&&(nameField.text?.count != 0)&&(passwordField.text?.count != 0)&&(verificationField.text?.count != 0){
            if passwordField.text == verificationField.text {
                print(passwordField.text)
                confirmBtn.isUserInteractionEnabled = true
                confirmBtn.backgroundColor = UIColor(red: 231/255.0, green: 124/255.0, blue: 142/255.0, alpha: 1)
            }else{
                confirmBtn.isUserInteractionEnabled = false
                confirmBtn.backgroundColor = .lightGray
            }
        }else{
            confirmBtn.isUserInteractionEnabled = false
            confirmBtn.backgroundColor = .lightGray
        }
    }
    
    func textFieldShouldReturn(_ textField: UITextField) -> Bool {
        textField.resignFirstResponder()
        return true
    }
}

//profile
extension RegisterViewController:UIImagePickerControllerDelegate,UINavigationControllerDelegate{
    
    @IBAction func click(_ sender:UIButton){
        let alert = UIAlertController(title: "选择图片", message: nil, preferredStyle: .actionSheet)
        alert.addAction(UIAlertAction(title: "拍照", style: .default,handler: {
            _ in self.openCamera()
        }))
        alert.addAction(UIAlertAction(title: "从照片中选择", style: .default,handler: {
            _ in self.openLabrary()
        }))
        alert.addAction(UIAlertAction(title: "取消", style: .cancel, handler: nil))
        
        self.present(alert, animated: true, completion: nil)
    }
    
    func imagePickerController(_ picker: UIImagePickerController, didFinishPickingMediaWithInfo info: [UIImagePickerController.InfoKey : Any]) {
        if let pickedImage = info[UIImagePickerController.InfoKey.editedImage] as? UIImage{
            pictureBtn.setImage(pickedImage, for: .normal)
        }
        picker.dismiss(animated: true, completion: nil)
    }
    
    func openCamera(){
        if (UIImagePickerController.isSourceTypeAvailable(UIImagePickerController.SourceType.camera)) {
            imagePicker.sourceType = UIImagePickerController.SourceType.camera
            imagePicker.allowsEditing = true
            self.present(imagePicker, animated: true, completion: nil)
        }else{
            let alert = UIAlertController(title: "警告", message: "未打开摄像头", preferredStyle: .alert)
            alert.addAction(UIAlertAction(title: "OK", style: .default, handler: nil))
            self.present(alert, animated: true, completion: nil)
            
        }
    }
    
    func openLabrary(){
        if (UIImagePickerController.isSourceTypeAvailable(UIImagePickerController.SourceType.photoLibrary)) {
            imagePicker.sourceType = UIImagePickerController.SourceType.photoLibrary
            imagePicker.allowsEditing = true
            self.present(imagePicker, animated: true, completion: nil)
        }else{
            let alert = UIAlertController(title: "警告", message: "没有权限访问照片", preferredStyle: .alert)
            alert.addAction(UIAlertAction(title: "OK", style: .default, handler: nil))
            self.present(alert, animated: true, completion: nil)
        }
    }
}
