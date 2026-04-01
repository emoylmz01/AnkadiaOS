# Ankadia OS (İşletim Sistemi)

![Ankadia OS](Boot_Ekrani.png)

Ankadia OS, "Ankadia" adlı Türkçe programlama dili için özel olarak tasarlanmış, mor temalı (Dark Purple) ve tamamen donanımdan izole bir şekilde x86 mimarisinde çalışan deneysel bir Mikro-Çekirdek İşletim Sistemi'dir.

## Proje Amacı
Bu projenin amacı klasik siyah-beyaz veya mavi ekranların ötesine geçerek, **tamamen Türkçe karakterleri** destekleyen, GUI (grafiksel menü) yapısına sahip, kendine has bir ekosistem yaratmaktır. Ana hedef, geliştirmiş olduğumuz Türkçe IDE'yi bir masaüstü uygulaması olmaktan çıkarıp bizzat işletim sistemine entegre etmektir. 

## Klasör Yapısı (V1.0.0)

- `/boot`: GRUB Multi-boot spesifikasyonları için x86 Assembly stubs (Bootloader).
- `/kernel`: C ile yazılmış, GDT (Global Descriptor Table), IDT ve Korumalı Mod donatılarını ayarlayan ana gövde.
- `/drivers`: Ekrana piksel veya yazı çizmek için VGA ekran adaptörü modülleri ve Türkçe karakter destekli (IRQ1 kesmesi) klavye okuma modülleri.
- `/gui`: Pencereleme sisteminin ön kısımları, "Double Buffering" mimarisine sahip çizim arabirimleri.
- `Makefile`: Sistemi hızlıca derlemek ve `ankadiaos.iso` çıktısı oluşturmak için derleme tanımlamaları.

## Gereksinimler ve Derleme İşlemi (Linux ortamında veya WSL'de)

Bu sistemi sıfırdan derlemek için bilgisayarınızda bir GCC cross-compiler (`i686-elf-gcc`) ve Assembly tarafı için nasm derleyicisi olmalıdır.

Sistemi QEMU ile emüle ederek çalıştırmak için aşağıdaki komutu kullanabilirsiniz:

```bash
make
make run
```

Eğer bir ISO oluşturup VirtualBox veya VMWare ile açmak isterseniz:
```bash
make iso
```

*(Not: Boot_Ekrani.png ve Arayuz_Ekrani.png demoları ekran görüntülerini içerir.)*
