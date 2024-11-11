#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Lớp cơ sở NhanVien
class NhanVien {
protected:
    string Hoten;
    string Ngaysinh;
    float Luongcoban;
public:
    NhanVien(string Hoten, string Ngaysinh, float Luongcoban)
        : Hoten(Hoten), Ngaysinh(Ngaysinh), Luongcoban(Luongcoban) {}
    virtual float tinhLuong() const = 0;
    virtual void xuatThongTin() const = 0;
    string getHoten() const {
        return Hoten;
    }
};

// Lớp NhanVienVanPhong kế thừa từ NhanVien
class NhanVienVanPhong : public NhanVien {
private:
    int Songaylamviec;
    float Trocap;
public:
    NhanVienVanPhong(string Hoten, string Ngaysinh, float Luongcoban, int Songaylamviec, float Trocap)
        : NhanVien(Hoten, Ngaysinh, Luongcoban), Songaylamviec(Songaylamviec), Trocap(Trocap) {}
    float tinhLuong() const override {
        return Luongcoban + Songaylamviec * 200000 + Trocap;
    }
    void xuatThongTin() const override {
        cout << "Nhan Vien Van Phong: " << Hoten << " - Luong: " << tinhLuong() << endl;
    }
};

// Lớp NhanVienSanXuat kế thừa từ NhanVien
class NhanVienSanXuat : public NhanVien {
private:
    int Sosanpham;
public:
    NhanVienSanXuat(string Hoten, string Ngaysinh, float Luongcoban, int Sosanpham)
        : NhanVien(Hoten, Ngaysinh, Luongcoban), Sosanpham(Sosanpham) {}
    float tinhLuong() const override {
        return Luongcoban + Sosanpham * 2000;
    }
    void xuatThongTin() const override {
        cout << "Nhan Vien San Xuat: " << Hoten << " - Luong: " << tinhLuong() << endl;
    }
};

// Lớp NhanVienQuanLy kế thừa từ NhanVien
class NhanVienQuanLy : public NhanVien {
private:
    float Hesochucvu;
    float Thuong;
public:
    NhanVienQuanLy(string Hoten, string Ngaysinh, float Luongcoban, float Hesochucvu, float Thuong)
        : NhanVien(Hoten, Ngaysinh, Luongcoban), Hesochucvu(Hesochucvu), Thuong(Thuong) {}
    float tinhLuong() const override {
        return Luongcoban * Hesochucvu + Thuong;
    }
    void xuatThongTin() const override {
        cout << "Nhan Vien Quan Ly: " << Hoten << " - Luong: " << tinhLuong() << endl;
    }
};

// Chương trình chính
int main() {
    vector<NhanVien*> danhSachNhanVien;
    int luaChon;
    // Nhập danh sách nhân viên
    do {
        cout << "Nhap 1 de them NV Van Phong, 2 de them NV San Xuat, 3 de them NV Quan Ly, 0 de ket thuc: ";
        cin >> luaChon;

        if (luaChon == 1) {
            string Hoten, Ngaysinh;
            float Luongcoban, Trocap;
            int Songaylamviec;

            cout << "Nhap ho ten: "; cin.ignore(); getline(cin, Hoten);
            cout << "Nhap ngay sinh: "; getline(cin, Ngaysinh);
            cout << "Nhap luong co ban: "; cin >> Luongcoban;
            cout << "Nhap so ngay lam viec: "; cin >> Songaylamviec;
            cout << "Nhap tro cap: "; cin >> Trocap;

            danhSachNhanVien.push_back(new NhanVienVanPhong(Hoten, Ngaysinh, Luongcoban, Songaylamviec, Trocap));
        } else if (luaChon == 2) {
            string Hoten, Ngaysinh;
            float Luongcoban;
            int Sosanpham;

            cout << "Nhap ho ten: "; cin.ignore(); getline(cin, Hoten);
            cout << "Nhap ngay sinh: "; getline(cin, Ngaysinh);
            cout << "Nhap luong co ban: "; cin >> Luongcoban;
            cout << "Nhap so san pham: "; cin >> Sosanpham;

            danhSachNhanVien.push_back(new NhanVienSanXuat(Hoten, Ngaysinh, Luongcoban, Sosanpham));
        } else if (luaChon == 3) {
            string Hoten, Ngaysinh;
            float Luongcoban, Hesochucvu, Thuong;

            cout << "Nhap ho ten: "; cin.ignore(); getline(cin, Hoten);
            cout << "Nhap ngay sinh: "; getline(cin, Ngaysinh);
            cout << "Nhap luong co ban: "; cin >> Luongcoban;
            cout << "Nhap he so chuc vu: "; cin >> Hesochucvu;
            cout << "Nhap Thuong: "; cin >> Thuong;

            danhSachNhanVien.push_back(new NhanVienQuanLy(Hoten, Ngaysinh, Luongcoban, Hesochucvu, Thuong));
        }
    } while (luaChon);
    // Xuất thông tin của các nhân viên và tính tổng lương công ty
    float tongLuong = 0;
    cout << "\nDanh sach nhan vien:\n";
    for (const auto& nv : danhSachNhanVien) {
        nv->xuatThongTin();
        tongLuong += nv->tinhLuong();
    }
    cout << "\nTong luong cua cong ty: " << tongLuong << endl;
    // Tìm kiếm nhân viên theo họ tên
    string tenTimKiem;
    cout << "\nNhap ho ten nhan vien can tim: ";
    cin.ignore();
    getline(cin, tenTimKiem);
    bool timThay = false;
    for (const auto& nv : danhSachNhanVien) {
        if (nv->getHoten() == tenTimKiem) {
            cout << "Thong tin nhan vien tim thay:\n";
            nv->xuatThongTin();
            timThay = true;
            break;
        }
    }
    if (!timThay) {
        cout << "Khong tim thay nhan vien co ten: " << tenTimKiem << endl;
    }
    return 0;
}
