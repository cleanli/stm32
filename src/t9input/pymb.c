#include "pyinput.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ο������粢�����޸�
//ALIENTEKս��STM32������
//ƴ�����뷨 ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/22
//�汾��V1.0			    
//�������������ӿƼ����޹�˾  	 												    								  
//////////////////////////////////////////////////////////////////////////////////

//�������б�
const unsigned char PY_mb_space []={""};
const unsigned char PY_mb_a     []={"������߹﹅����H����"};
const unsigned char PY_mb_ai    []={"�������������������������������������������"};
const unsigned char PY_mb_an    []={"�����������������ϰ����������������"};
const unsigned char PY_mb_ang   []={"�������a"};
const unsigned char PY_mb_ao    []={"�������������°ð���������������������������"};
const unsigned char PY_mb_ba    []={"�˰ͰְΰŰưǰȰɰʰ̰ϰаѰҰӰ԰���������������"};
const unsigned char PY_mb_bai   []={"�װذٰڰ۰ܰݰ޲�����"};
const unsigned char PY_mb_ban   []={"���߰������������������������"};
const unsigned char PY_mb_bang  []={"���������������������"};
const unsigned char PY_mb_bao   []={"�����������������������������������������������������"};
const unsigned char PY_mb_bei   []={"���������������������������������������������������������"};;
const unsigned char PY_mb_ben   []={"���������������"};
const unsigned char PY_mb_beng  []={"�������±ñı�ܡ���"};
const unsigned char PY_mb_bi    []={"�ƱǱȱɱʱ˱̱ͱαϱбѱұӱԱ�ذ�ֱױرٱڱ۱ܱ�������������ݩ��޵�������������������������������������������"};
const unsigned char PY_mb_bian  []={"�߱�����ޱ��������������������������������"};
const unsigned char PY_mb_biao  []={"������������������������"};
const unsigned char PY_mb_bie   []={"�������"};
const unsigned char PY_mb_bin   []={"������������������������������"};
const unsigned char PY_mb_bing  []={"������������������������������"};
const unsigned char PY_mb_bo    []={"�ذٰ�����������������������������������������������ެ�������������������"};
const unsigned char PY_mb_bu    []={"��������������������������߲�����������"};
const unsigned char PY_mb_ca    []={"������"};
const unsigned char PY_mb_cai   []={"�ŲƲǲ²òĲȲɲʲ˲�"};
const unsigned char PY_mb_can   []={"�ͲβϲвѲҲ����������"};
const unsigned char PY_mb_cang  []={"�Բղֲײ���"};
const unsigned char PY_mb_cao   []={"�ݲٲڲ۲�ܳ�������"};
const unsigned char PY_mb_ce    []={"����޲���"};
const unsigned char PY_mb_cen   []={"����"};
const unsigned char PY_mb_ceng  []={"�������"};
const unsigned char PY_mb_cha   []={"�������������ɲ���������������������"};
const unsigned char PY_mb_chai  []={"�����٭�������"};
const unsigned char PY_mb_chan  []={"���������������������������������������������"};
const unsigned char PY_mb_chang []={"�������������������������������������������������"};
const unsigned char PY_mb_chao  []={"�������������������½�������"};
const unsigned char PY_mb_che   []={"������������������"};
const unsigned char PY_mb_chen  []={"���������������³óĳ����������������"};
const unsigned char PY_mb_cheng []={"�ųƳǳȳɳʳ˳̳ͳγϳгѳҳ�ʢة�����������������������"};
const unsigned char PY_mb_chi   []={"�Գճֳ׳سٳڳ۳ܳݳ޳߳������߳������ܯ����������������������������"};
const unsigned char PY_mb_chong []={"����������������������"};
const unsigned char PY_mb_chou  []={"��������������ٱ������"};
const unsigned char PY_mb_chu   []={"����������������������������������ءۻ�������������������"};
const unsigned char PY_mb_chuai []={"����������"};
const unsigned char PY_mb_chuan []={"������������������������"};
const unsigned char PY_mb_chuang[]={"����������������"};
const unsigned char PY_mb_chui  []={"��������������"};
const unsigned char PY_mb_chun  []={"��������������ݻ����"};
const unsigned char PY_mb_chuo  []={"������������"};
const unsigned char PY_mb_ci    []={"�˴̴ʹ��Ų�ôĴŴƴǴȴɴ���������������"};
const unsigned char PY_mb_cong  []={"�ӴԴϴдѴ������������"};
const unsigned char PY_mb_cou   []={"������"};
const unsigned char PY_mb_cu    []={"�ִ״ش��������������"};
const unsigned char PY_mb_cuan  []={"�ڴ۴�����ߥ����"};
const unsigned char PY_mb_cui   []={"�ݴ޴ߴ����������������"};
const unsigned char PY_mb_cun   []={"��������"};
const unsigned char PY_mb_cuo   []={"��������������������������"};
const unsigned char PY_mb_da    []={"���������������������������"};
const unsigned char PY_mb_dai   []={"���������������������������ܤ߰߾��������"};
const unsigned char PY_mb_dan   []={"��������������������������������ʯ��������������������"};
const unsigned char PY_mb_dang  []={"�����������������������"};
const unsigned char PY_mb_dao   []={"��������������������������߶���������"};
const unsigned char PY_mb_de    []={"�µõĵ��"};
const unsigned char PY_mb_dei   []={"��"};
const unsigned char PY_mb_deng  []={"�εŵƵǵȵɵʵ������������"};
const unsigned char PY_mb_di    []={"�ĵֵ׵صٵڵ۵ܵݵ̵͵εϵеѵҵӵԵյ���ص��ڮ��ۡ��ݶ��������������������"};
const unsigned char PY_mb_dia   []={"��"};
const unsigned char PY_mb_dian  []={"�����������ߵ����������������������"};
const unsigned char PY_mb_diao  []={"���������������������"};
const unsigned char PY_mb_die   []={"����������������ܦ�����������"};
const unsigned char PY_mb_ding  []={"������������������������������������"};
const unsigned char PY_mb_diu   []={"����"};
const unsigned char PY_mb_dong  []={"��������������������������������"};
const unsigned char PY_mb_dou   []={"����������������������"};
const unsigned char PY_mb_du    []={"�Ƕȶɶ������������¶öĶŶƶ�ܶ�������������"};
const unsigned char PY_mb_duan  []={"�˶̶Ͷζ϶������"};
const unsigned char PY_mb_dui   []={"�ѶҶӶ�������"};
const unsigned char PY_mb_dun   []={"�ܶնֶ׶ضٶڶ۶���������������"};
const unsigned char PY_mb_duo   []={"���ȶ޶߶�����������������������"};
const unsigned char PY_mb_e     []={"�������������������Ŷج������ݭ��������������������"};
const unsigned char PY_mb_ei    []={"��"};
const unsigned char PY_mb_en    []={"������"};
const unsigned char PY_mb_er    []={"�������������������������"};
const unsigned char PY_mb_fa    []={"��������������������"};
const unsigned char PY_mb_fan   []={"����������������������������������ެ����������"};
const unsigned char PY_mb_fang  []={"���������������·÷ķ�������������"};
const unsigned char PY_mb_fei   []={"�ƷǷȷɷʷ˷̷ͷηϷз�����������������������������������"};
const unsigned char PY_mb_fen   []={"�ַҷܷݷ޷߷�ӷԷշ׷طٷڷ��������������"};
const unsigned char PY_mb_feng  []={"�����������������ٺۺ��������"};
const unsigned char PY_mb_fo    []={"��"};
const unsigned char PY_mb_fou   []={"���"};
const unsigned char PY_mb_fu    []={"���𸵸�����������������������������������������������������������������������������������������ۮܽ������ݳ����߻����������������������������������������������"};
const unsigned char PY_mb_ga    []={"���¼п�٤���������"};
const unsigned char PY_mb_gai   []={"�øĸŸƸǸȽ�ؤ���������"};
const unsigned char PY_mb_gan   []={"�ɸʸ˸̸͸θϸиѸҸ�������ߦ����������������"};
const unsigned char PY_mb_gang  []={"�Ըոָ׸ظٸڸ۸ܿ������"};
const unsigned char PY_mb_gao   []={"��޸߸�ݸ�����غھ۬޻��������"};
const unsigned char PY_mb_ge    []={"�����Ǹ�����������������������Ͽ�ت������ܪ��������������"};
const unsigned char PY_mb_gei   []={"��"};
const unsigned char PY_mb_gen   []={"����بݢ����"};
const unsigned char PY_mb_geng  []={"�����������������������"};
const unsigned char PY_mb_gong  []={"���������������������������������������"};
const unsigned char PY_mb_gou   []={"������������������ڸ��������������������"};
const unsigned char PY_mb_gu    []={"�ù����¹��������ĹŹƹǹȹɹʹ˹̹ͼ���ڬ��������������������������������������"};
const unsigned char PY_mb_gua   []={"�ιϹйѹҹ���ڴ�������"};
const unsigned char PY_mb_guai  []={"�Թչ���"};
const unsigned char PY_mb_guan  []={"�عٹڹ۹ܹݹ޹߹������ݸ������������"};
const unsigned char PY_mb_guang []={"������������"};
const unsigned char PY_mb_gui   []={"�������������������Ȳ���������������������"};
const unsigned char PY_mb_gun   []={"�������������"};
const unsigned char PY_mb_guo   []={"������������������������������������"};
const unsigned char PY_mb_ha    []={"������"};
const unsigned char PY_mb_hai   []={"���Ⱥ�������������������"};
const unsigned char PY_mb_han   []={"��������������������������������������������������������"};
const unsigned char PY_mb_hang  []={"�к��������������"};
const unsigned char PY_mb_hao   []={"�ºúĺ������尸亾��������޶�������"};
const unsigned char PY_mb_he    []={"�ǺȺɺʺ˺̺ͺκϺӺкѺҺԺպغֺ���ڭ�������������������"};
const unsigned char PY_mb_hei   []={"�ں�"};
const unsigned char PY_mb_hen   []={"�ۺܺݺ�"};
const unsigned char PY_mb_heng  []={"�ߺ����޿����"};
const unsigned char PY_mb_hong  []={"��������������ڧݦޮް����"};
const unsigned char PY_mb_hou   []={"���������ܩ��������������"};
const unsigned char PY_mb_hu    []={"���������˺��������������������������������������������������������������������������"};
const unsigned char PY_mb_hua   []={"��������������������������"};
const unsigned char PY_mb_huai  []={"������������"};
const unsigned char PY_mb_huan  []={"�����������������������»���佻�ۨۼ����ߧ���������������"};
const unsigned char PY_mb_huang []={"�λĻŻƻǻȻɻʻ˻̻ͻϻл��������������������"};
const unsigned char PY_mb_hui   []={"��ػٻڻһӻԻջֻ׻ۻܻݻ޻߻����������ڶ����ޥ���������������������"};
const unsigned char PY_mb_hun   []={"�������ڻ��������"};
const unsigned char PY_mb_huo   []={"�ͻ���������������޽߫������������"};
const unsigned char PY_mb_ji    []={"�ƼǸ��������������������������������������ȼɼʼ����������������������������������������������¼üļż˼̼ͽ���ϵآؽ����٥����ܸ����ݽ��ު��ߴ������������������������������������������������������������"};
const unsigned char PY_mb_jia   []={"�ҼӼμмѼԼռּ׼ؼټڼۼܼݼ޼�����٤ۣ���������������������������������"};
const unsigned char PY_mb_jian  []={"�������򽡼��߼�����������������������������������������������������������������������������������������������������"};
const unsigned char PY_mb_jiang []={"���罩����������������������ǿ����������������"};
const unsigned char PY_mb_jiao  []={"�нϾ���У�������������������������½ýĽŽƽȽɽʽ˽̽ͽν�ٮ��ܴ����������������������"};
const unsigned char PY_mb_jie   []={"������ҽܽӽԽ���ݽ޽սֽ׽ؽٽڽ۽߽�������ڦڵ�������������������������"};
const unsigned char PY_mb_jin   []={"�������������������������������������ݣ������������������������"};
const unsigned char PY_mb_jing  []={"������������������������������������������������������������ݼ������������������"};
const unsigned char PY_mb_jiong []={"����������"};
const unsigned char PY_mb_jiu   []={"�ž;Ⱦ��������¾þľƾɾʾ˾̾ξ�����������������"};
const unsigned char PY_mb_ju    []={"�޾߾���峵���ӾԾվ־׾ؾپھ۾ܾݾ���ϾоѾ���ڪ��������������������������������������������"};
const unsigned char PY_mb_juan  []={"���������Ȧ۲�������������"};
const unsigned char PY_mb_jue   []={"���������Ǿ����ž������������ܥާ���������������������"};
const unsigned char PY_mb_jun   []={"��������������������������������"};
const unsigned char PY_mb_ka    []={"��������������"};
const unsigned char PY_mb_kai   []={"�������������������������"};
const unsigned char PY_mb_kan   []={"������������٩�����ݨ�ۼ��"};
const unsigned char PY_mb_kang  []={"��������������������"};
const unsigned char PY_mb_kao   []={"����������������"};
const unsigned char PY_mb_ke    []={"�ɿʿ˿ƿ̿Ϳ�྿����¿ÿĿſǿ���������������������������������"};
const unsigned char PY_mb_ken   []={"�Ͽпѿ���"};
const unsigned char PY_mb_keng  []={"�ӿ������"};
const unsigned char PY_mb_kong  []={"�տֿ׿�������"};
const unsigned char PY_mb_kou   []={"�ٿڿۿ���ޢߵ����"};
const unsigned char PY_mb_ku    []={"�ݿ޿߿���������ܥ�"};
const unsigned char PY_mb_kua   []={"������٨�"};
const unsigned char PY_mb_kuai  []={"��������ۦ������"};
const unsigned char PY_mb_kuan  []={"������"};
const unsigned char PY_mb_kuang []={"�����������ڲڿ������������"};
const unsigned char PY_mb_kui   []={"����������������������ظ���������������������������"};
const unsigned char PY_mb_kun   []={"��������������������"};
const unsigned char PY_mb_kuo   []={"����������"};
const unsigned char PY_mb_la    []={"�������������������������"};
const unsigned char PY_mb_lai   []={"���������������������"};
const unsigned char PY_mb_lan   []={"����������������������������������������"};
const unsigned char PY_mb_lang  []={"������������������������ݹ"};
const unsigned char PY_mb_lao   []={"�������������������������������������"};
const unsigned char PY_mb_le    []={"��������߷����"};
const unsigned char PY_mb_lei   []={"��������������������������ڳ������������"};
const unsigned char PY_mb_leng  []={"������ܨ�"};
const unsigned char PY_mb_li    []={"��������������������������������������������������������������������تٳٵ۪����ݰ��޼߿�����������������������������������������������������������"};
const unsigned char PY_mb_lia   []={"��"};
const unsigned char PY_mb_lian  []={"������������������������������������������������"};
const unsigned char PY_mb_liang []={"������������������������ܮݹ�����"};
const unsigned char PY_mb_liao  []={"��������������������������ޤ������������"};
const unsigned char PY_mb_lie   []={"�������������������������"};
const unsigned char PY_mb_lin   []={"�����������������������������������������������"};
const unsigned char PY_mb_ling  []={"��������������������������������۹��������������������"};
const unsigned char PY_mb_liu   []={"����������������������µ½����������������"};
const unsigned char PY_mb_lo    []={"��"}; 
const unsigned char PY_mb_long  []={"��Ū��������¡¢£¤���������������"};
const unsigned char PY_mb_lou   []={"¥¦§¨©ª¶�����������������"};
const unsigned char PY_mb_lu    []={"��«¬­®¯°±²³´µ¶·¸¹º»¼½¾����ߣ������������������������������������"};
const unsigned char PY_mb_lv    []={"��������������������������¿�������������"}; 
const unsigned char PY_mb_luan  []={"������������"};
const unsigned char PY_mb_lue   []={"�����"};
const unsigned char PY_mb_lun   []={"����������������"};
const unsigned char PY_mb_luo   []={"���޸����������������������������������������������������"};
const unsigned char PY_mb_m     []={"߼"};  
const unsigned char PY_mb_ma    []={"������������������ĦĨ��������"};
const unsigned char PY_mb_mai   []={"������������������áܬ��������������"};
const unsigned char PY_mb_man   []={"����������á������"};
const unsigned char PY_mb_mang  []={"âãäåæç��������"};
const unsigned char PY_mb_mao   []={"èéêëì��îïðñòó��í������������������"};
const unsigned char PY_mb_me    []={"ô"};
const unsigned char PY_mb_mei   []={"ÿ����õö��������÷øùúûüýþ��ݮ�����������"};
const unsigned char PY_mb_men   []={"��������������"};
const unsigned char PY_mb_meng  []={"��������������������ޫ��������������"};
const unsigned char PY_mb_mi    []={"����������������������������������ڢ������������������������"};
const unsigned char PY_mb_mian  []={"�����������������������������"};
const unsigned char PY_mb_miao  []={"�������������������������������"};
const unsigned char PY_mb_mie   []={"����ؿ�����"};
const unsigned char PY_mb_min   []={"�������������������������������"};
const unsigned char PY_mb_ming  []={"������������ڤ���������"};
const unsigned char PY_mb_miu   []={"����"};
const unsigned char PY_mb_mo    []={"��û��ġĢģĤĥĦħĨĩĪīĬĭĮįİ���������������������������"};
const unsigned char PY_mb_mou   []={"ıĲĳٰ����������"};
const unsigned char PY_mb_mu    []={"ľĿ��ģĲĴĵĶķĸĹĺĻļĽ���������������"};
const unsigned char PY_mb_na    []={"����������������������"};
const unsigned char PY_mb_nai   []={"����������ؾ٦ܵ����"};
const unsigned char PY_mb_nan   []={"����������������"};
const unsigned char PY_mb_nang  []={"������߭��"};
const unsigned char PY_mb_nao   []={"����������ث������������"};
const unsigned char PY_mb_ne    []={"����ګ"};
const unsigned char PY_mb_nei   []={"����"};
const unsigned char PY_mb_nen   []={"����"};
const unsigned char PY_mb_neng  []={"��"};
const unsigned char PY_mb_ng    []={"��"}; 
const unsigned char PY_mb_ni    []={"������������������������٣������������������"};
const unsigned char PY_mb_nian  []={"��������������إ���������"};
const unsigned char PY_mb_niang []={"����"};
const unsigned char PY_mb_niao  []={"������������"};
const unsigned char PY_mb_nie   []={"�������������������ؿ�����"};
const unsigned char PY_mb_nin   []={"��"};
const unsigned char PY_mb_ning  []={"��������šŢ�������"};
const unsigned char PY_mb_niu   []={"ţŤťŦ�������"};
const unsigned char PY_mb_nong  []={"ŧŨũŪٯ��"};
const unsigned char PY_mb_nou   []={"��"};
const unsigned char PY_mb_nu    []={"ūŬŭ��������"};
const unsigned char PY_mb_nuan  []={"ů"};
const unsigned char PY_mb_nue   []={"űŰ"};
const unsigned char PY_mb_nuo   []={"��ŲųŴŵ�������"};
const unsigned char PY_mb_nv    []={"Ů������"};
const unsigned char PY_mb_o     []={"Ŷ���"};
const unsigned char PY_mb_ou    []={"ŷŸŹźŻżŽ��ک�����"};
const unsigned char PY_mb_pa    []={"�ǰ�žſ��������������"};
const unsigned char PY_mb_pai   []={"��������������ٽ����"};
const unsigned char PY_mb_pan   []={"�������������������������������������"};
const unsigned char PY_mb_pang  []={"����������������������"};
const unsigned char PY_mb_pao   []={"������������������������"};
const unsigned char PY_mb_pei   []={"�����������������������������"};
const unsigned char PY_mb_pen   []={"������"};
const unsigned char PY_mb_peng  []={"������������������������������ܡ���"};
const unsigned char PY_mb_pi    []={"�ٷ�����������������ơƢƣƤƥƦƧاƨƩ�����������ۯ����ܱ��ߨ�����������������������"};
const unsigned char PY_mb_pian  []={"���ƪƫƬƭ��������������"};
const unsigned char PY_mb_piao  []={"ƮƯưƱ����������������"};
const unsigned char PY_mb_pie   []={"ƲƳد���"};
const unsigned char PY_mb_pin   []={"ƴƵƶƷƸ�������"};
const unsigned char PY_mb_ping  []={"��ƹƺƻƼƽƾƿ����ٷ�����"};
const unsigned char PY_mb_po    []={"��������������������������۶�����������"};
const unsigned char PY_mb_pou   []={"������"};
const unsigned char PY_mb_pu    []={"�ձ������������������������������������������������"};
const unsigned char PY_mb_qi    []={"����������������������������������������������������������������������������������ؽ������������ٹ��ܻ��������������ޭ����������������������"};
const unsigned char PY_mb_qia   []={"����ǡǢ������"};
const unsigned char PY_mb_qian  []={"ǣǤǥǦǧǨǩǪǫǬǭǮǯǰǱǲǳǴǵǶǷǸ��ٻ����ܷ����ݡ�������������������������"};
const unsigned char PY_mb_qiang []={"ǹǺǻǼǽǾǿ�������������������������"};
const unsigned char PY_mb_qiao  []={"��������������������������������ȸڽ��������������������"};
const unsigned char PY_mb_qie   []={"����������٤�����ۧ������"};
const unsigned char PY_mb_qin   []={"��������������������������������������������"};
const unsigned char PY_mb_qing  []={"���������������������������������������������������"};
const unsigned char PY_mb_qiong []={"�����������������"};
const unsigned char PY_mb_qiu   []={"�������������������ٴ������������������������"};
const unsigned char PY_mb_qu    []={"����������������ȡȢȣȤȥ������ڰ۾����ޡ޾����������������������"};
const unsigned char PY_mb_quan  []={"ȦȧȨȩȪȫȬȭȮȯȰڹ�����������������"};
const unsigned char PY_mb_que   []={"ȱȲȳȴȵȶȷȸ������"};
const unsigned char PY_mb_qui   []={"��"};  
const unsigned char PY_mb_qun   []={"ȹȺ����"};
const unsigned char PY_mb_ran   []={"ȻȼȽȾ������"};
const unsigned char PY_mb_rang  []={"ȿ�����������"};
const unsigned char PY_mb_rao   []={"�����������"};
const unsigned char PY_mb_re    []={"������"};
const unsigned char PY_mb_ren   []={"�����������������������������������"};
const unsigned char PY_mb_reng  []={"����"};
const unsigned char PY_mb_ri    []={"��"};
const unsigned char PY_mb_rong  []={"������������������������������"};
const unsigned char PY_mb_rou   []={"������������"};
const unsigned char PY_mb_ru    []={"���������������������������޸�������"};
const unsigned char PY_mb_ruan  []={"������"};
const unsigned char PY_mb_rui   []={"�����������ި�"};
const unsigned char PY_mb_run   []={"����"};
const unsigned char PY_mb_ruo   []={"����ټ��"};
const unsigned char PY_mb_sa    []={"������ئ�����"};
const unsigned char PY_mb_sai   []={"����������"};
const unsigned char PY_mb_san   []={"����ɡɢ�����"};
const unsigned char PY_mb_sang  []={"ɣɤɥ�����"};
const unsigned char PY_mb_sao   []={"ɦɧɨɩ����ܣ����"};
const unsigned char PY_mb_se    []={"��ɪɫɬ����"};
const unsigned char PY_mb_sen   []={"ɭ"};
const unsigned char PY_mb_seng  []={"ɮ"};
const unsigned char PY_mb_sha   []={"ɯɰɱɲɳɴɵɶɷɼ��������������"};
const unsigned char PY_mb_shai  []={"ɫɸɹ"};
const unsigned char PY_mb_shan  []={"����ɺɻɼɽɾɿ��������������������դڨ�����������۷���������������������"};
const unsigned char PY_mb_shang []={"�������������������������"};
const unsigned char PY_mb_shao  []={"������������������������ۿ�����������"};
const unsigned char PY_mb_she   []={"�����������������������������������������"};
const unsigned char PY_mb_shei  []={"˭"}; 
const unsigned char PY_mb_shen  []={"����������������������������������ʲڷ��ݷ�������������"};
const unsigned char PY_mb_sheng []={"��������������ʡʢʣʤʥ����������"};
const unsigned char PY_mb_shi   []={"���³�ʦʮʯʧʨʩʪʫʬʭʰʱʲʳʴʵʶʷʸʹʺʻʼʽʾʿ����������������������������������������߱��ֳ������ݪ��������������������������"};
const unsigned char PY_mb_shou  []={"���������������������������"};
const unsigned char PY_mb_shu   []={"����������������������������������������������������������������ˡٿ�������ح���������������"};
const unsigned char PY_mb_shua  []={"ˢˣ�"};
const unsigned char PY_mb_shuai []={"��ˤ˥˦˧�"};
const unsigned char PY_mb_shuan []={"˨˩����"};
const unsigned char PY_mb_shuang[]={"˪˫ˬ����"};
const unsigned char PY_mb_shui  []={"ˮ˯˰˵��"};
const unsigned char PY_mb_shun  []={"˱˲˳˴"};
const unsigned char PY_mb_shuo  []={"��˵˶˷˸����������"};
const unsigned char PY_mb_si    []={"˹˺˻˼˽˾˿����������������������ٹ���������������������������"};
const unsigned char PY_mb_song  []={"��������������������������ݿڡ"};
const unsigned char PY_mb_sou   []={"�����������������������޴"};
const unsigned char PY_mb_su    []={"�����������������������������������������"};
const unsigned char PY_mb_suan  []={"�������"};
const unsigned char PY_mb_sui   []={"����������������������"};
const unsigned char PY_mb_sun   []={"������"};
const unsigned char PY_mb_suo   []={"�����������������������ɯ��������"};
const unsigned char PY_mb_ta    []={"����������̡̢��̣̤�����������������"};
const unsigned char PY_mb_tai   []={"̧̨̥̦̩̪̫̬̭��ۢ޷����������"};
const unsigned char PY_mb_tan   []={"��̴̵̶̷̸̮̯̰̱̲̳̹̺̻̼̽̾̿��۰������������"};
const unsigned char PY_mb_tang  []={"�������������������������������������������������"};
const unsigned char PY_mb_tao   []={"����������������������߶��������ػ"};
const unsigned char PY_mb_te    []={"��߯���"};
const unsigned char PY_mb_teng  []={"����������"};
const unsigned char PY_mb_ti    []={"���������������������������������������������"};
const unsigned char PY_mb_tian  []={"����������������������������"};
const unsigned char PY_mb_tiao  []={"������������٬������������������"};
const unsigned char PY_mb_tie   []={"�����������"};
const unsigned char PY_mb_ting  []={"������ͣͤͥͦͧ͢͡��������������"};
const unsigned char PY_mb_tong  []={"ͩͫͬͭͮͯͰͱͲͳʹ١��������ͪ���������"};
const unsigned char PY_mb_tou   []={"͵Ͷͷ͸������"};
const unsigned char PY_mb_tu    []={"͹ͺͻͼͽ;Ϳ��������ܢݱ������"};
const unsigned char PY_mb_tuan  []={"���������"};
const unsigned char PY_mb_tui   []={"��������������"};
const unsigned char PY_mb_tun   []={"�����������������"};
const unsigned char PY_mb_tuo   []={"˵������������������������ر٢����������������������"};
const unsigned char PY_mb_wa    []={"�������������������"};
const unsigned char PY_mb_wai   []={"������"};
const unsigned char PY_mb_wan   []={"��������������������������������������ܹݸ��������������"};
const unsigned char PY_mb_wang  []={"�����������������������������"};
const unsigned char PY_mb_wei   []={"Ϊλν��Ρ΢ΣΤάΥΦΧΨΩΫέήίΰαβγδεζηθικμξο������������ޱ�����������������������������������"};
const unsigned char PY_mb_wen   []={"�������������������������������"};
const unsigned char PY_mb_weng  []={"��������޳"};
const unsigned char PY_mb_wo    []={"���������������������ݫ��������"};
const unsigned char PY_mb_wu    []={"�����������������������أ����������������������������������������������������������������������������������"};
const unsigned char PY_mb_xi    []={"ϣϰϦϷϸ����������������������ϡ��ϢϤϥϧϨϪϫϬϮϯϱϲϴϵ϶���������������ϭϩϳ��������ۭݾ���������������������������������������������"};
const unsigned char PY_mb_xia   []={"ϹϺϻϼϽϾϿ���������������������������"};
const unsigned char PY_mb_xian  []={"������������������ϳϴ��������������������������������������ݲ޺������������������������������"};
const unsigned char PY_mb_xiang []={"������������������������������������������ܼ������������"};
const unsigned char PY_mb_xiao  []={"С��Ф��������������������ТУХЦЧ���������������������"};
const unsigned char PY_mb_xie   []={"ЩЪЫЬЭЮЯабвгдежзийклмѪ��ШҶ��������ޯߢ���������������������"};
const unsigned char PY_mb_xin   []={"ноп��������������ܰݷ����ض����"};
const unsigned char PY_mb_xing  []={"��ʡ�����������������������������������ߩ���"};
const unsigned char PY_mb_xiong []={"��������������ܺ"};
const unsigned char PY_mb_xiu   []={"������������������������������������"};
const unsigned char PY_mb_xu    []={"��������������������������������������ڼ������ޣ������������������"};
const unsigned char PY_mb_xuan  []={"��ѡ��������������Ѥ��ѣѢ����������������������ȯ"};
const unsigned char PY_mb_xue   []={"��ѥѦѧѨѩѪ����������"};
const unsigned char PY_mb_xun   []={"ѰѮѸѶѯѵѫѬѭѱѲѳѴѷۨ����޹������࿣ݡަ����������"};
const unsigned char PY_mb_ya    []={"��ѿ����ѹ��ѺѻѼѽѾ�����������������������������������"};
const unsigned char PY_mb_yan   []={"��������������������������������������������������������������������������������ٲ��Ǧ����������ڥ����۱۳ܾ�����������������������������"};
const unsigned char PY_mb_yang  []={"�������������������������������������������������"};
const unsigned char PY_mb_yao   []={"Ҫ��ҧҩ����ҡҢ���ңҤҥҦҨҫԿزس��ߺ����ű�����������������������"};
const unsigned char PY_mb_ye    []={"ҲҳҵҶҹҺҬҭҮүҰұҴҷҸа��������������������"};
const unsigned char PY_mb_yi    []={"һ��������������������ҼҽҾҿ�������������������������������������������������������������������������β��������٫ڱ������ܲ����޲������߽߮�����������������������������������������������������������������"};
const unsigned char PY_mb_yin   []={"����ӡ����������������������������ط�۴����ܧ������������������"};
const unsigned char PY_mb_ying  []={"ӳӰӢӨөӪӫӣӤӥӦӧӬӭӮӯӱӲ��ݺ�����������۫�������������������"};
const unsigned char PY_mb_yo    []={"Ӵ���"};
const unsigned char PY_mb_yong  []={"��ӵӶ��ӿӷӸӹӺӻӼӽӾ����ٸ��ܭ�����������"};
const unsigned char PY_mb_you   []={"��������������������������������������������������������٧ݬݯݵ��������������������"};
const unsigned char PY_mb_yu    []={"������������������ԡ������������������������������������������������������������ԢԣԤԥԦ��ع�����εξخ��ٶ��������������������������������������������������������������������������"};
const unsigned char PY_mb_yuan  []={"ԭԪ԰ԱԲԴԵԶԸԹԺԧԨԩԫԬԮԯԳԷ��ܫܾ������������������"};
const unsigned char PY_mb_yue   []={"��������˵ԻԼԽԾԿ����������������"};
const unsigned char PY_mb_yun   []={"��Ա�������������������������ܿ��۩����������"};
const unsigned char PY_mb_za    []={"��������զ����"};
const unsigned char PY_mb_zai   []={"������������������"};
const unsigned char PY_mb_zan   []={"���������������������"};
const unsigned char PY_mb_zang  []={"�����������"};
const unsigned char PY_mb_zao   []={"������������������������������"};
const unsigned char PY_mb_ze    []={"��������զ�����������������"};
const unsigned char PY_mb_zei   []={"��"};
const unsigned char PY_mb_zen   []={"����"};
const unsigned char PY_mb_zeng  []={"��������������"};
const unsigned char PY_mb_zha   []={"��բ����������ագդեզէըթ߸��������������������"};
const unsigned char PY_mb_zhai  []={"լխծ����ժիկ���"};
const unsigned char PY_mb_zhan  []={"ռսվչմ��հձղճյնշոպ��ջտ�������"};
const unsigned char PY_mb_zhang []={"�������������������������˳������������۵���"};
const unsigned char PY_mb_zhao  []={"����צ���׳�����گ������������������"};
const unsigned char PY_mb_zhe   []={"������������������������ߡ��������������"};
const unsigned char PY_mb_zhen  []={"��������������������������������֡����������������������������"};
const unsigned char PY_mb_zheng []={"��֤��������������������֢֣ں����������"};
const unsigned char PY_mb_zhi   []={"��������ֻ֧ʶִֵֹ��ּֽ֥֭֮־ְֱֲֳֶַָֺֿ֦֪֫֬֯��������������֨֩������������ش��ۤ������������������������������������������������������������"};
const unsigned char PY_mb_zhong []={"����������������������ڣ���������"};
const unsigned char PY_mb_zhou  []={"����������������������������ݧ����������������"};
const unsigned char PY_mb_zhu   []={"��סעף������������������������������������������פ������٪����ۥ��������������������������������ؼ"};
const unsigned char PY_mb_zhua  []={"ץצ��"};
const unsigned char PY_mb_zhuai []={"קת"};
const unsigned char PY_mb_zhuan []={"��רשת׫׬׭�������"};
const unsigned char PY_mb_zhuang[]={"��׮ׯװױײ׳״����"};
const unsigned char PY_mb_zhui  []={"׵׶׷׸׹׺�������"};
const unsigned char PY_mb_zhun  []={"׻׼����"};
const unsigned char PY_mb_zhuo  []={"��׽׾׿��������������پ��ߪ������������"};
const unsigned char PY_mb_zi    []={"���������������������������������֨��������������������������������������"};
const unsigned char PY_mb_zong  []={"����������������������"};
const unsigned char PY_mb_zou   []={"������������۸����"};
const unsigned char PY_mb_zu    []={"����������������������"};
const unsigned char PY_mb_zuan  []={"��߬������"};
const unsigned char PY_mb_zui   []={"��������ީ��"};
const unsigned char PY_mb_zun   []={"��������ߤ"};
const unsigned char PY_mb_zuo   []={"�����������������������������������"};

//ƴ��������
const py_index py_index3[]=
{
{"" ,"",(unsigned char*)PY_mb_space},
{"2","a",(unsigned char*)PY_mb_a},
{"3","e",(unsigned char*)PY_mb_e},
{"6","o",(unsigned char*)PY_mb_o},
{"24","ai",(unsigned char*)PY_mb_ai},
{"26","an",(unsigned char*)PY_mb_an},
{"26","ao",(unsigned char*)PY_mb_ao},
{"22","ba",(unsigned char*)PY_mb_ba},
{"24","bi",(unsigned char*)PY_mb_bi},
{"26","bo",(unsigned char*)PY_mb_bo},
{"28","bu",(unsigned char*)PY_mb_bu},
{"22","ca",(unsigned char*)PY_mb_ca},
{"23","ce",(unsigned char*)PY_mb_ce},
{"24","ci",(unsigned char*)PY_mb_ci},
{"28","cu",(unsigned char*)PY_mb_cu},
{"32","da",(unsigned char*)PY_mb_da},
{"33","de",(unsigned char*)PY_mb_de},
{"34","di",(unsigned char*)PY_mb_di},
{"38","du",(unsigned char*)PY_mb_du},
{"36","en",(unsigned char*)PY_mb_en},
{"37","er",(unsigned char*)PY_mb_er},
{"32","fa",(unsigned char*)PY_mb_fa},
{"36","fo",(unsigned char*)PY_mb_fo},
{"38","fu",(unsigned char*)PY_mb_fu},
{"42","ha",(unsigned char*)PY_mb_ha},
{"42","ga",(unsigned char*)PY_mb_ga},
{"43","ge",(unsigned char*)PY_mb_ge},
{"43","he",(unsigned char*)PY_mb_he},
{"48","gu",(unsigned char*)PY_mb_gu},
{"48","hu",(unsigned char*)PY_mb_hu},
{"54","ji",(unsigned char*)PY_mb_ji},
{"58","ju",(unsigned char*)PY_mb_ju},
{"52","ka",(unsigned char*)PY_mb_ka},
{"53","ke",(unsigned char*)PY_mb_ke},
{"58","ku",(unsigned char*)PY_mb_ku},
{"52","la",(unsigned char*)PY_mb_la},
{"53","le",(unsigned char*)PY_mb_le},
{"54","li",(unsigned char*)PY_mb_li},
{"58","lu",(unsigned char*)PY_mb_lu},
{"58","lv",(unsigned char*)PY_mb_lv},
{"62","ma",(unsigned char*)PY_mb_ma},
{"63","me",(unsigned char*)PY_mb_me},
{"64","mi",(unsigned char*)PY_mb_mi},
{"66","mo",(unsigned char*)PY_mb_mo},
{"68","mu",(unsigned char*)PY_mb_mu},
{"62","na",(unsigned char*)PY_mb_na},
{"63","ne",(unsigned char*)PY_mb_ne},
{"64","ni",(unsigned char*)PY_mb_ni},
{"68","nu",(unsigned char*)PY_mb_nu},
{"68","nv",(unsigned char*)PY_mb_nv},
{"68","ou",(unsigned char*)PY_mb_ou},
{"72","pa",(unsigned char*)PY_mb_pa},
{"74","pi",(unsigned char*)PY_mb_pi},
{"76","po",(unsigned char*)PY_mb_po},
{"78","pu",(unsigned char*)PY_mb_pu},
{"74","qi",(unsigned char*)PY_mb_qi},
{"78","qu",(unsigned char*)PY_mb_qu},
{"73","re",(unsigned char*)PY_mb_re},
{"74","ri",(unsigned char*)PY_mb_ri},
{"78","ru",(unsigned char*)PY_mb_ru},
{"72","sa",(unsigned char*)PY_mb_sa},
{"73","se",(unsigned char*)PY_mb_se},
{"74","si",(unsigned char*)PY_mb_si},
{"78","su",(unsigned char*)PY_mb_su},
{"82","ta",(unsigned char*)PY_mb_ta},
{"83","te",(unsigned char*)PY_mb_te},
{"84","ti",(unsigned char*)PY_mb_ti},
{"88","tu",(unsigned char*)PY_mb_tu},
{"92","wa",(unsigned char*)PY_mb_wa},
{"96","wo",(unsigned char*)PY_mb_wo},
{"98","wu",(unsigned char*)PY_mb_wu},
{"94","xi",(unsigned char*)PY_mb_xi},
{"98","xu",(unsigned char*)PY_mb_xu},
{"92","ya",(unsigned char*)PY_mb_ya},
{"93","ye",(unsigned char*)PY_mb_ye},
{"94","yi",(unsigned char*)PY_mb_yi},
{"96","yo",(unsigned char*)PY_mb_yo},
{"98","yu",(unsigned char*)PY_mb_yu},
{"92","za",(unsigned char*)PY_mb_za},
{"93","ze",(unsigned char*)PY_mb_ze},
{"94","zi",(unsigned char*)PY_mb_zi},
{"98","zu",(unsigned char*)PY_mb_zu},
{"264","ang",(unsigned char*)PY_mb_ang},
{"224","bai",(unsigned char*)PY_mb_bai},
{"226","ban",(unsigned char*)PY_mb_ban},
{"226","bao",(unsigned char*)PY_mb_bao},
{"234","bei",(unsigned char*)PY_mb_bei},
{"236","ben",(unsigned char*)PY_mb_ben},
{"243","bie",(unsigned char*)PY_mb_bie},
{"246","bin",(unsigned char*)PY_mb_bin},
{"224","cai",(unsigned char*)PY_mb_cai},
{"226","can",(unsigned char*)PY_mb_can},
{"226","cao",(unsigned char*)PY_mb_cao},
{"242","cha",(unsigned char*)PY_mb_cha},
{"243","che",(unsigned char*)PY_mb_che},
{"244","chi",(unsigned char*)PY_mb_chi},
{"248","chu",(unsigned char*)PY_mb_chu},
{"268","cou",(unsigned char*)PY_mb_cou},
{"284","cui",(unsigned char*)PY_mb_cui},
{"286","cun",(unsigned char*)PY_mb_cun},
{"286","cuo",(unsigned char*)PY_mb_cuo},
{"324","dai",(unsigned char*)PY_mb_dai},
{"326","dan",(unsigned char*)PY_mb_dan},
{"326","dao",(unsigned char*)PY_mb_dao},
{"334","dei",(unsigned char*)PY_mb_dei},
{"343","die",(unsigned char*)PY_mb_die},
{"348","diu",(unsigned char*)PY_mb_diu},
{"368","dou",(unsigned char*)PY_mb_dou},
{"384","dui",(unsigned char*)PY_mb_dui},
{"386","dun",(unsigned char*)PY_mb_dun},
{"386","duo",(unsigned char*)PY_mb_duo},								
{"326","fan",(unsigned char*)PY_mb_fan},
{"334","fei",(unsigned char*)PY_mb_fei},
{"336","fen",(unsigned char*)PY_mb_fen},
{"368","fou",(unsigned char*)PY_mb_fou},
{"424","gai",(unsigned char*)PY_mb_gai},
{"426","gan",(unsigned char*)PY_mb_gan},
{"426","gao",(unsigned char*)PY_mb_gao},
{"434","gei",(unsigned char*)PY_mb_gei},
{"436","gen",(unsigned char*)PY_mb_gan},
{"468","gou",(unsigned char*)PY_mb_gou},
{"482","gua",(unsigned char*)PY_mb_gua},
{"484","gui",(unsigned char*)PY_mb_gui},
{"486","gun",(unsigned char*)PY_mb_gun},
{"486","guo",(unsigned char*)PY_mb_guo},
{"424","hai",(unsigned char*)PY_mb_hai},
{"426","han",(unsigned char*)PY_mb_han},
{"426","hao",(unsigned char*)PY_mb_hao},
{"434","hei",(unsigned char*)PY_mb_hei},
{"436","hen",(unsigned char*)PY_mb_hen},
{"468","hou",(unsigned char*)PY_mb_hou},
{"482","hua",(unsigned char*)PY_mb_hua},
{"484","hui",(unsigned char*)PY_mb_hui},
{"486","hun",(unsigned char*)PY_mb_hun},
{"486","huo",(unsigned char*)PY_mb_huo},
{"542","jia",(unsigned char*)PY_mb_jia},
{"543","jie",(unsigned char*)PY_mb_jie},
{"546","jin",(unsigned char*)PY_mb_jin},
{"548","jiu",(unsigned char*)PY_mb_jiu},
{"583","jue",(unsigned char*)PY_mb_jue},
{"586","jun",(unsigned char*)PY_mb_jun},
{"524","kai",(unsigned char*)PY_mb_kai},
{"526","kan",(unsigned char*)PY_mb_kan},
{"526","kao",(unsigned char*)PY_mb_kao},
{"536","ken",(unsigned char*)PY_mb_ken},
{"568","kou",(unsigned char*)PY_mb_kou},
{"582","kua",(unsigned char*)PY_mb_kua},
{"584","kui",(unsigned char*)PY_mb_kui},
{"586","kun",(unsigned char*)PY_mb_kun},
{"586","kuo",(unsigned char*)PY_mb_kuo},
{"524","lai",(unsigned char*)PY_mb_lai},
{"526","lan",(unsigned char*)PY_mb_lan},
{"526","lao",(unsigned char*)PY_mb_lao},
{"534","lei",(unsigned char*)PY_mb_lei},
{"543","lie",(unsigned char*)PY_mb_lie},
{"546","lin",(unsigned char*)PY_mb_lin},
{"548","liu",(unsigned char*)PY_mb_liu},
{"568","lou",(unsigned char*)PY_mb_lou},
{"583","lue",(unsigned char*)PY_mb_lue},
{"586","lun",(unsigned char*)PY_mb_lun},
{"586","luo",(unsigned char*)PY_mb_luo},
{"624","mai",(unsigned char*)PY_mb_mai},
{"626","man",(unsigned char*)PY_mb_man},
{"626","mao",(unsigned char*)PY_mb_mao},
{"634","mei",(unsigned char*)PY_mb_mei},
{"636","men",(unsigned char*)PY_mb_men},
{"643","mie",(unsigned char*)PY_mb_mie},
{"646","min",(unsigned char*)PY_mb_min},
{"648","miu",(unsigned char*)PY_mb_miu},
{"668","mou",(unsigned char*)PY_mb_mou},
{"624","nai",(unsigned char*)PY_mb_nai},
{"626","nan",(unsigned char*)PY_mb_nan},
{"626","nao",(unsigned char*)PY_mb_nao},
{"634","nei",(unsigned char*)PY_mb_nei},
{"636","nen",(unsigned char*)PY_mb_nen},
{"643","nie",(unsigned char*)PY_mb_nie},
{"646","nin",(unsigned char*)PY_mb_nin},
{"648","niu",(unsigned char*)PY_mb_niu},
{"683","nue",(unsigned char*)PY_mb_nue},
{"686","nuo",(unsigned char*)PY_mb_nuo},
{"724","pai",(unsigned char*)PY_mb_pai},
{"726","pan",(unsigned char*)PY_mb_pan},
{"726","pao",(unsigned char*)PY_mb_pao},
{"734","pei",(unsigned char*)PY_mb_pei},
{"736","pen",(unsigned char*)PY_mb_pen},
{"743","pie",(unsigned char*)PY_mb_pie},
{"746","pin",(unsigned char*)PY_mb_pin},
{"768","pou",(unsigned char*)PY_mb_pou},
{"742","qia",(unsigned char*)PY_mb_qia},
{"743","qie",(unsigned char*)PY_mb_qie},
{"746","qin",(unsigned char*)PY_mb_qin},
{"748","qiu",(unsigned char*)PY_mb_qiu},
{"783","que",(unsigned char*)PY_mb_que},
{"786","qun",(unsigned char*)PY_mb_qun},
{"726","ran",(unsigned char*)PY_mb_ran},
{"726","rao",(unsigned char*)PY_mb_rao},
{"736","ren",(unsigned char*)PY_mb_ren},
{"768","rou",(unsigned char*)PY_mb_rou},
{"784","rui",(unsigned char*)PY_mb_rui},
{"786","run",(unsigned char*)PY_mb_run},
{"786","ruo",(unsigned char*)PY_mb_ruo},
{"724","sai",(unsigned char*)PY_mb_sai},
{"726","sao",(unsigned char*)PY_mb_sao},
{"726","san",(unsigned char*)PY_mb_san},
{"736","sen",(unsigned char*)PY_mb_sen},
{"742","sha",(unsigned char*)PY_mb_sha},
{"743","she",(unsigned char*)PY_mb_she},
{"744","shi",(unsigned char*)PY_mb_shi},
{"748","shu",(unsigned char*)PY_mb_shu},
{"768","sou",(unsigned char*)PY_mb_sou},
{"784","sui",(unsigned char*)PY_mb_sui},
{"786","sun",(unsigned char*)PY_mb_sun},
{"786","suo",(unsigned char*)PY_mb_suo},
{"824","tai",(unsigned char*)PY_mb_tai},
{"826","tan",(unsigned char*)PY_mb_tan},
{"826","tao",(unsigned char*)PY_mb_tao},
{"843","tie",(unsigned char*)PY_mb_tie},
{"868","tou",(unsigned char*)PY_mb_tou},
{"884","tui",(unsigned char*)PY_mb_tui},
{"886","tun",(unsigned char*)PY_mb_tun},
{"886","tuo",(unsigned char*)PY_mb_tuo},
{"924","wai",(unsigned char*)PY_mb_wai},
{"926","wan",(unsigned char*)PY_mb_wan},
{"934","wei",(unsigned char*)PY_mb_wei},
{"936","wen",(unsigned char*)PY_mb_wen},
{"942","xia",(unsigned char*)PY_mb_xia},
{"943","xie",(unsigned char*)PY_mb_xie},
{"946","xin",(unsigned char*)PY_mb_xin},
{"948","xiu",(unsigned char*)PY_mb_xiu},
{"983","xue",(unsigned char*)PY_mb_xue},
{"986","xun",(unsigned char*)PY_mb_xun},
{"926","yan",(unsigned char*)PY_mb_yan},
{"926","yao",(unsigned char*)PY_mb_yao},
{"946","yin",(unsigned char*)PY_mb_yin},
{"968","you",(unsigned char*)PY_mb_you},
{"983","yue",(unsigned char*)PY_mb_yue},
{"986","yun",(unsigned char*)PY_mb_yun},
{"924","zai",(unsigned char*)PY_mb_zai},
{"926","zan",(unsigned char*)PY_mb_zan},
{"926","zao",(unsigned char*)PY_mb_zao},
{"934","zei",(unsigned char*)PY_mb_zei},
{"936","zen",(unsigned char*)PY_mb_zen},
{"942","zha",(unsigned char*)PY_mb_zha},
{"943","zhe",(unsigned char*)PY_mb_zhe},
{"944","zhi",(unsigned char*)PY_mb_zhi},
{"948","zhu",(unsigned char*)PY_mb_zhu},
{"968","zou",(unsigned char*)PY_mb_zou},
{"984","zui",(unsigned char*)PY_mb_zui},
{"986","zun",(unsigned char*)PY_mb_zun},
{"986","zuo",(unsigned char*)PY_mb_zuo},
{"2264","bang",(unsigned char*)PY_mb_bang},
{"2364","beng",(unsigned char*)PY_mb_beng},
{"2426","bian",(unsigned char*)PY_mb_bian},
{"2426","biao",(unsigned char*)PY_mb_biao},
{"2464","bing",(unsigned char*)PY_mb_bing},
{"2264","cang",(unsigned char*)PY_mb_cang},
{"2364","ceng",(unsigned char*)PY_mb_ceng},
{"2424","chai",(unsigned char*)PY_mb_chai},
{"2426","chan",(unsigned char*)PY_mb_chan},
{"2426","chao",(unsigned char*)PY_mb_chao},
{"2436","chen",(unsigned char*)PY_mb_chen},
{"2468","chou",(unsigned char*)PY_mb_chou},
{"2484","chuai",(unsigned char*)PY_mb_chuai},
{"2484","chui",(unsigned char*)PY_mb_chui},
{"2486","chun",(unsigned char*)PY_mb_chun},
{"2486","chuo",(unsigned char*)PY_mb_chuo},
{"2664","cong",(unsigned char*)PY_mb_cong},
{"2826","cuan",(unsigned char*)PY_mb_cuan},
{"3264","dang",(unsigned char*)PY_mb_dang},
{"3364","deng",(unsigned char*)PY_mb_deng},
{"3426","dian",(unsigned char*)PY_mb_dian},
{"3426","diao",(unsigned char*)PY_mb_diao},
{"3464","ding",(unsigned char*)PY_mb_ding},
{"3664","dong",(unsigned char*)PY_mb_dong},
{"3826","duan",(unsigned char*)PY_mb_duan},
{"3264","fang",(unsigned char*)PY_mb_fang},
{"3364","feng",(unsigned char*)PY_mb_feng},
{"4264","gang",(unsigned char*)PY_mb_gang},
{"4364","geng",(unsigned char*)PY_mb_geng},
{"4664","gong",(unsigned char*)PY_mb_gong},
{"4824","guai",(unsigned char*)PY_mb_guai},
{"4826","guan",(unsigned char*)PY_mb_guan},
{"4264","hang",(unsigned char*)PY_mb_hang},
{"4364","heng",(unsigned char*)PY_mb_heng},
{"4664","hong",(unsigned char*)PY_mb_hong},
{"4823","huai",(unsigned char*)PY_mb_huai},
{"4826","huan",(unsigned char*)PY_mb_huan},
{"5426","jian",(unsigned char*)PY_mb_jian},
{"5426","jiao",(unsigned char*)PY_mb_jiao},
{"5464","jing",(unsigned char*)PY_mb_jing},
{"5826","juan",(unsigned char*)PY_mb_juan},
{"5264","kang",(unsigned char*)PY_mb_kang},
{"5364","keng",(unsigned char*)PY_mb_keng},
{"5664","kong",(unsigned char*)PY_mb_kong},
{"5824","kuai",(unsigned char*)PY_mb_kuai},
{"5826","kuan",(unsigned char*)PY_mb_kuan},
{"5264","lang",(unsigned char*)PY_mb_lang},
{"5366","leng",(unsigned char*)PY_mb_leng},
{"5426","lian",(unsigned char*)PY_mb_lian},
{"5426","liao",(unsigned char*)PY_mb_liao},
{"5464","ling",(unsigned char*)PY_mb_ling},
{"5664","long",(unsigned char*)PY_mb_long},
{"5826","luan",(unsigned char*)PY_mb_luan},
{"6264","mang",(unsigned char*)PY_mb_mang},
{"6364","meng",(unsigned char*)PY_mb_meng},
{"6426","mian",(unsigned char*)PY_mb_mian},
{"6426","miao",(unsigned char*)PY_mb_miao},
{"6464","ming",(unsigned char*)PY_mb_ming},
{"6264","nang",(unsigned char*)PY_mb_nang},
{"6364","neng",(unsigned char*)PY_mb_neng},
{"6426","nian",(unsigned char*)PY_mb_nian},
{"6426","niao",(unsigned char*)PY_mb_niao},
{"6464","ning",(unsigned char*)PY_mb_ning},
{"6664","nong",(unsigned char*)PY_mb_nong},
{"6826","nuan",(unsigned char*)PY_mb_nuan},
{"7264","pang",(unsigned char*)PY_mb_pang},
{"7364","peng",(unsigned char*)PY_mb_peng},
{"7426","pian",(unsigned char*)PY_mb_pian},
{"7426","piao",(unsigned char*)PY_mb_piao},
{"7464","ping",(unsigned char*)PY_mb_ping},
{"7426","qian",(unsigned char*)PY_mb_qian},
{"7426","qiao",(unsigned char*)PY_mb_qiao},
{"7464","qing",(unsigned char*)PY_mb_qing},
{"7826","quan",(unsigned char*)PY_mb_quan},
{"7264","rang",(unsigned char*)PY_mb_rang},
{"7364","reng",(unsigned char*)PY_mb_reng},
{"7664","rong",(unsigned char*)PY_mb_rong},
{"7826","ruan",(unsigned char*)PY_mb_ruan},
{"7264","sang",(unsigned char*)PY_mb_sang},
{"7364","seng",(unsigned char*)PY_mb_seng},
{"7424","shai",(unsigned char*)PY_mb_shai},
{"7426","shan",(unsigned char*)PY_mb_shan},
{"7426","shao",(unsigned char*)PY_mb_shao},
{"7434","shei",(unsigned char*)PY_mb_shei},
{"7436","shen",(unsigned char*)PY_mb_shen},    
{"7468","shou",(unsigned char*)PY_mb_shou},
{"7482","shua",(unsigned char*)PY_mb_shua},
{"7484","shui",(unsigned char*)PY_mb_shui},
{"7486","shun",(unsigned char*)PY_mb_shun},
{"7486","shuo",(unsigned char*)PY_mb_shuo},
{"7664","song",(unsigned char*)PY_mb_song},
{"7826","suan",(unsigned char*)PY_mb_suan},
{"8264","tang",(unsigned char*)PY_mb_tang},
{"8364","teng",(unsigned char*)PY_mb_teng},
{"8426","tian",(unsigned char*)PY_mb_tian},
{"8426","tiao",(unsigned char*)PY_mb_tiao},
{"8464","ting",(unsigned char*)PY_mb_ting},
{"8664","tong",(unsigned char*)PY_mb_tong},
{"8826","tuan",(unsigned char*)PY_mb_tuan},
{"9264","wang",(unsigned char*)PY_mb_wang},
{"9364","weng",(unsigned char*)PY_mb_weng},
{"9426","xian",(unsigned char*)PY_mb_xian},
{"9426","xiao",(unsigned char*)PY_mb_xiao},
{"9464","xing",(unsigned char*)PY_mb_xing},
{"9826","xuan",(unsigned char*)PY_mb_xuan},
{"9264","yang",(unsigned char*)PY_mb_yang},
{"9464","ying",(unsigned char*)PY_mb_ying},
{"9664","yong",(unsigned char*)PY_mb_yong},
{"9826","yuan",(unsigned char*)PY_mb_yuan},
{"9264","zang",(unsigned char*)PY_mb_zang},
{"9364","zeng",(unsigned char*)PY_mb_zeng},
{"9424","zhai",(unsigned char*)PY_mb_zhai},
{"9426","zhan",(unsigned char*)PY_mb_zhan},
{"9426","zhao",(unsigned char*)PY_mb_zhao},
{"9436","zhen",(unsigned char*)PY_mb_zhen},
{"9468","zhou",(unsigned char*)PY_mb_zhou},
{"9482","zhua",(unsigned char*)PY_mb_zhua},
{"9484","zhui",(unsigned char*)PY_mb_zhui},
{"9486","zhun",(unsigned char*)PY_mb_zhun},
{"9486","zhuo",(unsigned char*)PY_mb_zhuo},
{"9664","zong",(unsigned char*)PY_mb_zong},
{"9826","zuan",(unsigned char*)PY_mb_zuan},
{"24264","chang",(unsigned char*)PY_mb_chang},
{"24364","cheng",(unsigned char*)PY_mb_cheng},
{"24664","chong",(unsigned char*)PY_mb_chong},
{"24826","chuan",(unsigned char*)PY_mb_chuan},
{"48264","guang",(unsigned char*)PY_mb_guang},
{"48264","huang",(unsigned char*)PY_mb_huang},
{"54264","jiang",(unsigned char*)PY_mb_jiang},
{"54664","jiong",(unsigned char*)PY_mb_jiong},
{"58264","kuang",(unsigned char*)PY_mb_kuang},
{"54264","liang",(unsigned char*)PY_mb_liang},
{"64264","niang",(unsigned char*)PY_mb_niang},
{"74264","qiang",(unsigned char*)PY_mb_qiang},
{"74664","qiong",(unsigned char*)PY_mb_qiong},
{"74264","shang ",(unsigned char*)PY_mb_shang},
{"74364","sheng",(unsigned char*)PY_mb_sheng},
{"74824","shuai",(unsigned char*)PY_mb_shuai},
{"74826","shuan",(unsigned char*)PY_mb_shuan},
{"94264","xiang",(unsigned char*)PY_mb_xiang},
{"94664","xiong",(unsigned char*)PY_mb_xiong},
{"94264","zhang",(unsigned char*)PY_mb_zhang},
{"94364","zheng",(unsigned char*)PY_mb_zheng},
{"94664","zhong",(unsigned char*)PY_mb_zhong},
{"94824","zhuai",(unsigned char*)PY_mb_zhuai},
{"94826","zhuan",(unsigned char*)PY_mb_zhuan},
{"248264","chuang",(unsigned char*)PY_mb_chuang},
{"748264","shuang",(unsigned char*)PY_mb_shuang},
{"948264","zhuang",(unsigned char*)PY_mb_zhuang},
};

int size_of_pyindex()
{
	return sizeof(py_index3)/sizeof(py_index3[0]);
}
