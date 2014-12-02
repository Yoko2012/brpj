--------------------------------------------
-- Export file for user USHOW2            --
-- Created by wyx on 2014-10-21, 14:25:40 --
--------------------------------------------

spool ushow2_gongsi_1021.log

prompt
prompt Creating table TB_ALARM_CAR
prompt ===========================
prompt
create table TB_ALARM_CAR
(
  nid         NUMBER not null,
  ncamera     NUMBER default 1,
  scarnumber  VARCHAR2(100),
  scolour     VARCHAR2(100),
  stype       VARCHAR2(100),
  sdirection  VARCHAR2(100),
  scolor      VARCHAR2(100),
  ndegree     NUMBER,
  dgettime    DATE,
  nflag       NUMBER default 0,
  dcreate     DATE default sysdate,
  bpicture    BLOB,
  sfile       VARCHAR2(260),
  nsize       NUMBER,
  scameraname VARCHAR2(100),
  sip         VARCHAR2(100),
  blackid     NUMBER
)
;
comment on table TB_ALARM_CAR
  is '����ʶ������';
comment on column TB_ALARM_CAR.nid
  is '����ID';
comment on column TB_ALARM_CAR.ncamera
  is '����ͷ���';
comment on column TB_ALARM_CAR.scarnumber
  is '���ƺ�';
comment on column TB_ALARM_CAR.scolour
  is '������ɫ';
comment on column TB_ALARM_CAR.stype
  is '��������';
comment on column TB_ALARM_CAR.sdirection
  is '��������';
comment on column TB_ALARM_CAR.scolor
  is '��ɫ������';
comment on column TB_ALARM_CAR.ndegree
  is '���Ŷ�';
comment on column TB_ALARM_CAR.dgettime
  is '����ʱ��';
comment on column TB_ALARM_CAR.nflag
  is '�����ʶ��0δ����1�Ѵ���';
comment on column TB_ALARM_CAR.dcreate
  is '���ʱ��';
comment on column TB_ALARM_CAR.bpicture
  is '��Ƭ';
comment on column TB_ALARM_CAR.sfile
  is '�ļ�·��';
comment on column TB_ALARM_CAR.nsize
  is '��Ƭ��С';
comment on column TB_ALARM_CAR.scameraname
  is '����ͷ����';
comment on column TB_ALARM_CAR.sip
  is '����ͷIP';
comment on column TB_ALARM_CAR.blackid
  is '������ID';
create index ALARM_CAR_INDEX on TB_ALARM_CAR (DCREATE);
alter table TB_ALARM_CAR
  add constraint ALARM_CAR_NID primary key (NID);

prompt
prompt Creating table TB_ALARM_VEHICLE
prompt ===============================
prompt
create table TB_ALARM_VEHICLE
(
  nid         NUMBER not null,
  ncamera     NUMBER default 1,
  scarnumber  VARCHAR2(100),
  scolour     VARCHAR2(100),
  stype       VARCHAR2(100),
  sdirection  VARCHAR2(100),
  scolor      VARCHAR2(100),
  ndegree     NUMBER,
  dgettime    DATE,
  nflag       NUMBER default 0,
  dcreate     DATE default sysdate,
  bpicture    BLOB,
  sfile       VARCHAR2(260),
  nsize       NUMBER,
  scameraname VARCHAR2(100),
  sip         VARCHAR2(100),
  blackid     NUMBER
)
;
comment on table TB_ALARM_VEHICLE
  is '�綯��ʶ������';
comment on column TB_ALARM_VEHICLE.nid
  is '����ID';
comment on column TB_ALARM_VEHICLE.ncamera
  is '����ͷ���';
comment on column TB_ALARM_VEHICLE.scarnumber
  is '�綯���ƺ�';
comment on column TB_ALARM_VEHICLE.scolour
  is '�綯��������ɫ';
comment on column TB_ALARM_VEHICLE.stype
  is '�綯������';
comment on column TB_ALARM_VEHICLE.sdirection
  is '�綯������';
comment on column TB_ALARM_VEHICLE.scolor
  is '��ɫ������';
comment on column TB_ALARM_VEHICLE.ndegree
  is '���Ŷ�';
comment on column TB_ALARM_VEHICLE.dgettime
  is '����ʱ��';
comment on column TB_ALARM_VEHICLE.nflag
  is '�����ʶ��0δ����1�Ѵ���';
comment on column TB_ALARM_VEHICLE.dcreate
  is '���ʱ��';
comment on column TB_ALARM_VEHICLE.bpicture
  is '��Ƭ';
comment on column TB_ALARM_VEHICLE.sfile
  is '�ļ�·��';
comment on column TB_ALARM_VEHICLE.nsize
  is '��Ƭ��С';
comment on column TB_ALARM_VEHICLE.scameraname
  is '����ͷ����';
comment on column TB_ALARM_VEHICLE.sip
  is '����ͷIP';
comment on column TB_ALARM_VEHICLE.blackid
  is '������ID';
create index ALARM_VEHICLE_INDEX on TB_ALARM_VEHICLE (DCREATE);
alter table TB_ALARM_VEHICLE
  add constraint ALARM_VEHICLE_NID primary key (NID);

prompt
prompt Creating table TB_CAMERA_INFO
prompt =============================
prompt
create table TB_CAMERA_INFO
(
  objectid                INTEGER not null,
  sadministrativedivision VARCHAR2(100),
  sstreet                 VARCHAR2(100),
  spolicestation          VARCHAR2(100),
  ssecurityarea           VARCHAR2(100),
  slivingareasname        VARCHAR2(100),
  saddress                VARCHAR2(100),
  fheight                 NUMBER(19,10),
  stype                   VARCHAR2(100),
  fresolution             NUMBER(19,10),
  sequipmentmanufacture   VARCHAR2(100),
  susage                  VARCHAR2(100),
  sowership               VARCHAR2(100),
  stelphone               VARCHAR2(20),
  fx                      NUMBER(19,10),
  fy                      NUMBER(19,10),
  areatype                NUMBER(19,10),
  smark1                  VARCHAR2(100),
  smark2                  VARCHAR2(100),
  smark3                  VARCHAR2(100),
  sip                     VARCHAR2(100),
  personflag              NUMBER(1),
  carflag                 NUMBER(1),
  fabricflag              NUMBER(1),
  canceltime              DATE,
  status                  VARCHAR2(20),
  sport                   VARCHAR2(30),
  schannel                VARCHAR2(30),
  suser                   VARCHAR2(30),
  spwd                    VARCHAR2(30),
  nmachineid              NUMBER(19,10),
  sorgno                  VARCHAR2(20),
  scameraname             VARCHAR2(1000),
  sipserver               VARCHAR2(100),
  sipcent                 VARCHAR2(100),
  sportcent               VARCHAR2(30),
  sportserver             VARCHAR2(30)
)
;
comment on table TB_CAMERA_INFO
  is '����ͷ��Ϣ';
comment on column TB_CAMERA_INFO.objectid
  is '����';
comment on column TB_CAMERA_INFO.sadministrativedivision
  is '��������';
comment on column TB_CAMERA_INFO.sstreet
  is '�ֵ�';
comment on column TB_CAMERA_INFO.spolicestation
  is '�ɳ���';
comment on column TB_CAMERA_INFO.ssecurityarea
  is '������';
comment on column TB_CAMERA_INFO.slivingareasname
  is 'С������';
comment on column TB_CAMERA_INFO.saddress
  is '��ϸ��ַ';
comment on column TB_CAMERA_INFO.fheight
  is '��װ�߶�';
comment on column TB_CAMERA_INFO.stype
  is '����ͷ����';
comment on column TB_CAMERA_INFO.fresolution
  is '�ֱ���';
comment on column TB_CAMERA_INFO.sequipmentmanufacture
  is '�豸����';
comment on column TB_CAMERA_INFO.susage
  is '��;';
comment on column TB_CAMERA_INFO.sowership
  is '��Ȩ��λ';
comment on column TB_CAMERA_INFO.stelphone
  is '��ϵ��ʽ';
comment on column TB_CAMERA_INFO.fx
  is 'X����';
comment on column TB_CAMERA_INFO.fy
  is 'Y����';
comment on column TB_CAMERA_INFO.areatype
  is 'Ӧ�ó��������ֶ�Ŀǰ���ã�TS_CAMERA_SCENE_RELATION��չ��';
comment on column TB_CAMERA_INFO.smark1
  is '�����ֶ�';
comment on column TB_CAMERA_INFO.smark2
  is '�����ֶ�';
comment on column TB_CAMERA_INFO.smark3
  is '�����ֶ�';
comment on column TB_CAMERA_INFO.sip
  is 'IP��ַ';
comment on column TB_CAMERA_INFO.personflag
  is 'ץ���������־��1��';
comment on column TB_CAMERA_INFO.carflag
  is 'ץ�ĳ������־��1��';
comment on column TB_CAMERA_INFO.fabricflag
  is 'ץ���������־��1��';
comment on column TB_CAMERA_INFO.canceltime
  is 'ע��ʱ��';
comment on column TB_CAMERA_INFO.status
  is '����ͷ״̬��1����������������';
comment on column TB_CAMERA_INFO.sport
  is '�˿ں�';
comment on column TB_CAMERA_INFO.schannel
  is 'ͨ����';
comment on column TB_CAMERA_INFO.suser
  is '�û���';
comment on column TB_CAMERA_INFO.spwd
  is '����';
comment on column TB_CAMERA_INFO.nmachineid
  is '��Ӧ�ķ�����ID';
comment on column TB_CAMERA_INFO.sorgno
  is '�ɳ����������';
comment on column TB_CAMERA_INFO.scameraname
  is '����ͷ����';
comment on column TB_CAMERA_INFO.sipserver
  is '�����IP';
comment on column TB_CAMERA_INFO.sipcent
  is '����IP';
comment on column TB_CAMERA_INFO.sportcent
  is '���Ķ˿ں�';
comment on column TB_CAMERA_INFO.sportserver
  is '����˶˿ں�';
alter table TB_CAMERA_INFO
  add constraint CAMERA_INFO_OBJECTID primary key (OBJECTID);

prompt
prompt Creating table TB_CAR_BLACK
prompt ===========================
prompt
create table TB_CAR_BLACK
(
  nid        NUMBER not null,
  scarnumber VARCHAR2(100),
  sbrand     VARCHAR2(255),
  slostname  VARCHAR2(100),
  sphone     VARCHAR2(100),
  smark      VARCHAR2(1000)
)
;
comment on table TB_CAR_BLACK
  is '�������������ȶ�Դ��';
comment on column TB_CAR_BLACK.nid
  is '���';
comment on column TB_CAR_BLACK.scarnumber
  is '���ƺ�';
comment on column TB_CAR_BLACK.sbrand
  is 'Ʒ��';
comment on column TB_CAR_BLACK.slostname
  is 'ʧ������
';
comment on column TB_CAR_BLACK.sphone
  is '��ϵ�绰
';
comment on column TB_CAR_BLACK.smark
  is '������Ϣ
';
alter table TB_CAR_BLACK
  add constraint CAR_BLACK_NID primary key (NID);

prompt
prompt Creating table TB_DETECT_SERVER
prompt ===============================
prompt
create table TB_DETECT_SERVER
(
  nid        NUMBER not null,
  sip        VARCHAR2(32),
  isoccupy   NUMBER default 0,
  channelnum NUMBER,
  isenable   NUMBER default 0,
  lasttime   DATE default sysdate,
  missionid  NUMBER,
  ncamera    NUMBER default 0
)
;
comment on table TB_DETECT_SERVER
  is '�ֲ�ʽʶ���豸��';
comment on column TB_DETECT_SERVER.nid
  is 'ʶ�������ID';
comment on column TB_DETECT_SERVER.sip
  is '������IP';
comment on column TB_DETECT_SERVER.isoccupy
  is 'ռ��״̬ 0δ��ռ�� 1ռ��';
comment on column TB_DETECT_SERVER.channelnum
  is '��N· �������';
comment on column TB_DETECT_SERVER.isenable
  is '����״̬ 0���� 1����';
comment on column TB_DETECT_SERVER.lasttime
  is '���� ʱ��ȶ�';
comment on column TB_DETECT_SERVER.missionid
  is '�������÷�����������ID Ԥ��ռ������ID';
comment on column TB_DETECT_SERVER.ncamera
  is 'Ԥ��ռ�õ�����ͷID�� ��ֹ��δ���';

prompt
prompt Creating table TB_DEVICE
prompt ========================
prompt
create table TB_DEVICE
(
  scameraname VARCHAR2(200),
  sipserver   VARCHAR2(32),
  sport       NUMBER,
  suser       VARCHAR2(30),
  spwd        VARCHAR2(200),
  ncamera     NUMBER not null,
  nid         VARCHAR2(30),
  svenderid   NUMBER,
  channel     NUMBER,
  rtspurl     VARCHAR2(500),
  rtpmode     NUMBER,
  decodetag   NUMBER,
  detectip    VARCHAR2(32),
  isplay      NUMBER default 0,
  userid      NUMBER,
  userlv      NUMBER,
  longitude   VARCHAR2(32),
  latitude    VARCHAR2(32),
  crossindex  VARCHAR2(64),
  crossid     NUMBER,
  detectid    NUMBER
)
;
comment on table TB_DEVICE
  is '�豸��';
comment on column TB_DEVICE.scameraname
  is '����ͷ����';
comment on column TB_DEVICE.sipserver
  is '����ͷIP';
comment on column TB_DEVICE.sport
  is '�˿ں�';
comment on column TB_DEVICE.suser
  is '�û���';
comment on column TB_DEVICE.spwd
  is '����';
comment on column TB_DEVICE.ncamera
  is '����ͷid';
comment on column TB_DEVICE.nid
  is '���������T_ZD_ORG.nid';
comment on column TB_DEVICE.svenderid
  is '���������ID,0������1�� ';
comment on column TB_DEVICE.channel
  is 'ͨ����';
comment on column TB_DEVICE.rtspurl
  is 'RTSP ����ַ';
comment on column TB_DEVICE.rtpmode
  is '��ý�崫��ģʽ 0=RTP-RTSP 1=RTP-UDP';
comment on column TB_DEVICE.decodetag
  is '��ý������־ 0=haikang 1=ga_h264';
comment on column TB_DEVICE.detectip
  is '���Ÿ�����ͷ��ʶ�������IP';
comment on column TB_DEVICE.isplay
  is 'ʶ������� �Ƿ�ʶ��  0 δʶ�� 1ʶ��';
comment on column TB_DEVICE.userid
  is '������豸���û�NID';
comment on column TB_DEVICE.userlv
  is '������豸���û�����';
comment on column TB_DEVICE.longitude
  is '����';
comment on column TB_DEVICE.latitude
  is 'γ��';
comment on column TB_DEVICE.crossindex
  is '����������';
comment on column TB_DEVICE.crossid
  is '����ID';
comment on column TB_DEVICE.detectid
  is '���Ÿ�����ͷ��ʶ�������ID';
alter table TB_DEVICE
  add constraint DEVICE_NCAMERA primary key (NCAMERA);

prompt
prompt Creating table TB_LOG
prompt =====================
prompt
create table TB_LOG
(
  nid         NUMBER not null,
  dcreatetime DATE default SYSDATE,
  susername   VARCHAR2(32),
  smark       VARCHAR2(1024)
)
;
comment on table TB_LOG
  is 'ϵͳ��־��';
comment on column TB_LOG.nid
  is '����';
comment on column TB_LOG.dcreatetime
  is '���ʱ��';
comment on column TB_LOG.susername
  is '�û���';
comment on column TB_LOG.smark
  is '��־��Ϣ';
create index LOG_INDEX on TB_LOG (DCREATETIME);
alter table TB_LOG
  add constraint PRI_LOG_NID primary key (NID);

prompt
prompt Creating table TB_MATCH_RESULT_CAR
prompt ==================================
prompt
create table TB_MATCH_RESULT_CAR
(
  nid         NUMBER not null,
  ncamera     NUMBER default 1,
  scarnumber  VARCHAR2(100),
  scolour     VARCHAR2(100),
  stype       VARCHAR2(100),
  sdirection  VARCHAR2(100),
  ndegree     NUMBER,
  dgettime    DATE,
  nflag       NUMBER default 0,
  dcreate     DATE default sysdate,
  bpicture    BLOB,
  sfile       VARCHAR2(260),
  scolor      VARCHAR2(100),
  nsize       NUMBER,
  scameraname VARCHAR2(100),
  sip         VARCHAR2(100)
)
;
comment on table TB_MATCH_RESULT_CAR
  is '����������';
comment on column TB_MATCH_RESULT_CAR.nid
  is '����ID';
comment on column TB_MATCH_RESULT_CAR.ncamera
  is '����ͷ���';
comment on column TB_MATCH_RESULT_CAR.scarnumber
  is '���ƺ�';
comment on column TB_MATCH_RESULT_CAR.scolour
  is '������ɫ';
comment on column TB_MATCH_RESULT_CAR.stype
  is '��������';
comment on column TB_MATCH_RESULT_CAR.sdirection
  is '��������';
comment on column TB_MATCH_RESULT_CAR.ndegree
  is '���Ŷ�';
comment on column TB_MATCH_RESULT_CAR.dgettime
  is '����ʱ��';
comment on column TB_MATCH_RESULT_CAR.nflag
  is '������־ 1 ���� 0 ������';
comment on column TB_MATCH_RESULT_CAR.dcreate
  is '���ʱ��';
comment on column TB_MATCH_RESULT_CAR.bpicture
  is '��Ƭ';
comment on column TB_MATCH_RESULT_CAR.sfile
  is '�ļ�·��';
comment on column TB_MATCH_RESULT_CAR.scolor
  is '��ɫ������';
comment on column TB_MATCH_RESULT_CAR.nsize
  is '��Ƭ��С';
comment on column TB_MATCH_RESULT_CAR.scameraname
  is '����ͷ����';
comment on column TB_MATCH_RESULT_CAR.sip
  is '����ͷIP';
create index MATCH_RESULT_CAR_INDEX on TB_MATCH_RESULT_CAR (DCREATE);
alter table TB_MATCH_RESULT_CAR
  add constraint MACTCH_RESULT_CAR_ID primary key (NID);

prompt
prompt Creating table TB_MATCH_RESULT_VEHICLE
prompt ======================================
prompt
create table TB_MATCH_RESULT_VEHICLE
(
  nid         NUMBER not null,
  ncamera     NUMBER default 1,
  scarnumber  VARCHAR2(100),
  scolour     VARCHAR2(100),
  stype       VARCHAR2(100),
  sdirection  VARCHAR2(100),
  ndegree     NUMBER,
  dgettime    DATE,
  nflag       NUMBER default 0,
  dcreate     DATE default sysdate,
  bpicture    BLOB,
  sfile       VARCHAR2(260),
  scolor      VARCHAR2(100),
  nsize       NUMBER,
  scameraname VARCHAR2(100),
  sip         VARCHAR2(100)
)
;
comment on table TB_MATCH_RESULT_VEHICLE
  is '�綯��������';
comment on column TB_MATCH_RESULT_VEHICLE.nid
  is '����ID';
comment on column TB_MATCH_RESULT_VEHICLE.ncamera
  is '����ͷ���';
comment on column TB_MATCH_RESULT_VEHICLE.scarnumber
  is '�綯���ƺ�';
comment on column TB_MATCH_RESULT_VEHICLE.scolour
  is '�綯��������ɫ';
comment on column TB_MATCH_RESULT_VEHICLE.stype
  is '�綯������';
comment on column TB_MATCH_RESULT_VEHICLE.sdirection
  is '�綯������';
comment on column TB_MATCH_RESULT_VEHICLE.ndegree
  is '���Ŷ�';
comment on column TB_MATCH_RESULT_VEHICLE.dgettime
  is '����ʱ��';
comment on column TB_MATCH_RESULT_VEHICLE.nflag
  is '������־ 1 ���� 0 ������';
comment on column TB_MATCH_RESULT_VEHICLE.dcreate
  is '���ʱ��';
comment on column TB_MATCH_RESULT_VEHICLE.bpicture
  is '��Ƭ';
comment on column TB_MATCH_RESULT_VEHICLE.sfile
  is '�ļ�·��';
comment on column TB_MATCH_RESULT_VEHICLE.scolor
  is '��ɫ������';
comment on column TB_MATCH_RESULT_VEHICLE.nsize
  is '��Ƭ��С';
comment on column TB_MATCH_RESULT_VEHICLE.scameraname
  is '����ͷ����';
comment on column TB_MATCH_RESULT_VEHICLE.sip
  is '����ͷIP';
create index MATCH_RESULT_VEHICLE_INDEX on TB_MATCH_RESULT_VEHICLE (DCREATE);
alter table TB_MATCH_RESULT_VEHICLE
  add constraint MATCH_RESULT_VEHICLE_NID primary key (NID);

prompt
prompt Creating table TB_MISSION
prompt =========================
prompt
create table TB_MISSION
(
  nid      NUMBER not null,
  userid   NUMBER,
  detectid NUMBER,
  isplay   NUMBER,
  ncamera  NUMBER,
  flag     NUMBER default 0,
  indate   DATE default sysdate,
  message  VARCHAR2(256)
)
;
comment on table TB_MISSION
  is '�����';
comment on column TB_MISSION.nid
  is '����ID';
comment on column TB_MISSION.userid
  is '�����û�ID';
comment on column TB_MISSION.detectid
  is 'ʶ�������ID';
comment on column TB_MISSION.isplay
  is '������ͷ���в��� 0ֹͣ 1����';
comment on column TB_MISSION.ncamera
  is '����ͷID';
comment on column TB_MISSION.flag
  is '�����ݶ�ȡ��־ 0δ��ȡ  1��ת���Ѷ�ȡ 2ʶ�����Ѷ�ȡ';
comment on column TB_MISSION.indate
  is '���ʱ��';
comment on column TB_MISSION.message
  is '��������ʾ����Ϣ';
alter table TB_MISSION
  add constraint MISSION_NID primary key (NID);

prompt
prompt Creating table TB_RECORD_PLAN
prompt =============================
prompt
create table TB_RECORD_PLAN
(
  nid         NUMBER not null,
  ncamera     NUMBER,
  scameraarea VARCHAR2(260),
  scameraname VARCHAR2(260),
  sip         VARCHAR2(32),
  dailyflag   NUMBER,
  dateflag    NUMBER,
  weekflag    NUMBER,
  enableflag  NUMBER,
  startweek   NUMBER,
  endweek     NUMBER,
  starttime   DATE,
  endtime     DATE
)
;
comment on table TB_RECORD_PLAN
  is '��ʱ¼�Ƽƻ���';
comment on column TB_RECORD_PLAN.nid
  is '����';
comment on column TB_RECORD_PLAN.ncamera
  is '����ͷID  ';
comment on column TB_RECORD_PLAN.scameraarea
  is '����ͷ����  ';
comment on column TB_RECORD_PLAN.scameraname
  is '����ͷ����   ';
comment on column TB_RECORD_PLAN.sip
  is '����ͷip��ַ   ';
comment on column TB_RECORD_PLAN.dailyflag
  is '�ռƻ�¼�Ʊ�־ ';
comment on column TB_RECORD_PLAN.dateflag
  is 'ʱ���¼�Ʊ�־ ';
comment on column TB_RECORD_PLAN.weekflag
  is '�ܼƻ�¼�Ʊ�־  ';
comment on column TB_RECORD_PLAN.enableflag
  is '����¼�Ʊ�־ ';
comment on column TB_RECORD_PLAN.startweek
  is '�ܼƻ��Ŀ�ʼ   ';
comment on column TB_RECORD_PLAN.endweek
  is '�ܼƻ��Ľ���  ';
comment on column TB_RECORD_PLAN.starttime
  is '��ʼʱ��    ';
comment on column TB_RECORD_PLAN.endtime
  is '����ʱ��    ';
alter table TB_RECORD_PLAN
  add constraint RECORD_PLAN_NID primary key (NID);

prompt
prompt Creating table TB_USER
prompt ======================
prompt
create table TB_USER
(
  suser             VARCHAR2(100),
  spwd              VARCHAR2(200),
  ndeviceallot      NUMBER,
  nphoto            NUMBER,
  nvideo            NUMBER,
  nview             NUMBER,
  nalarm            NUMBER,
  nyuntai           NUMBER,
  nparam            NUMBER,
  nvideoset         NUMBER,
  ncarnumber        NUMBER,
  nblack            NUMBER,
  nset              NUMBER,
  nvideoquery       NUMBER,
  nalarmquery       NUMBER,
  ndistinguishquery NUMBER,
  nlogquery         NUMBER,
  nmanager          NUMBER,
  nid               NUMBER not null,
  nlevel            NUMBER,
  ndetectlimit      NUMBER
)
;
comment on table TB_USER
  is '�û���';
comment on column TB_USER.suser
  is '�û���';
comment on column TB_USER.spwd
  is '����';
comment on column TB_USER.ndeviceallot
  is '�豸����';
comment on column TB_USER.nphoto
  is 'ץ��ͼƬ';
comment on column TB_USER.nvideo
  is '����¼��';
comment on column TB_USER.nview
  is 'Ԥ������';
comment on column TB_USER.nalarm
  is 'ʶ�𱨾�����';
comment on column TB_USER.nyuntai
  is '��̨����';
comment on column TB_USER.nparam
  is 'ϵͳ��������';
comment on column TB_USER.nvideoset
  is '¼������';
comment on column TB_USER.ncarnumber
  is '����ʶ��';
comment on column TB_USER.nblack
  is '����
������';
comment on column TB_USER.nset
  is '����';
comment on column TB_USER.nvideoquery
  is 'ϵͳ��Ƶ��ѯ';
comment on column TB_USER.nalarmquery
  is 'ϵͳ������ѯ';
comment on column TB_USER.ndistinguishquery
  is 'ϵͳʶ���ѯ';
comment on column TB_USER.nlogquery
  is 'ϵͳ��־��ѯ';
comment on column TB_USER.nmanager
  is '����ԱȨ��
';
comment on column TB_USER.nid
  is '�ؼ���';
comment on column TB_USER.nlevel
  is '���� ֵԽС Ȩ��Խ��';
comment on column TB_USER.ndetectlimit
  is 'ʶ����������';
alter table TB_USER
  add constraint USER_NID primary key (NID);

prompt
prompt Creating table TB_VEHICLE_BLACK
prompt ===============================
prompt
create table TB_VEHICLE_BLACK
(
  nid        NUMBER not null,
  scarnumber VARCHAR2(100),
  sbrand     VARCHAR2(255),
  slostname  VARCHAR2(100),
  sphone     VARCHAR2(100),
  smark      VARCHAR2(1000)
)
;
comment on table TB_VEHICLE_BLACK
  is '�綯�����������ȶ�Դ��';
comment on column TB_VEHICLE_BLACK.nid
  is '���';
comment on column TB_VEHICLE_BLACK.scarnumber
  is '�綯�����ƺ�';
comment on column TB_VEHICLE_BLACK.sbrand
  is 'Ʒ��';
comment on column TB_VEHICLE_BLACK.slostname
  is 'ʧ������
';
comment on column TB_VEHICLE_BLACK.sphone
  is '��ϵ�绰
';
comment on column TB_VEHICLE_BLACK.smark
  is '������Ϣ
';
create index VEHICLE_BLACK_INDEX on TB_VEHICLE_BLACK (NID);
alter table TB_VEHICLE_BLACK
  add constraint VEHICLE_BLACK_NID primary key (NID);

prompt
prompt Creating table TB_VIDEO
prompt =======================
prompt
create table TB_VIDEO
(
  nid         NUMBER not null,
  scameraname VARCHAR2(260),
  sip         VARCHAR2(260),
  svenderid   NUMBER,
  dgettime    DATE default sysdate,
  sformat     VARCHAR2(20),
  sfilesize   NUMBER,
  dstarttime  DATE,
  dendtime    DATE,
  spath       VARCHAR2(260)
)
;
comment on table TB_VIDEO
  is '��Ƶ��Ϣ';
comment on column TB_VIDEO.nid
  is '���';
comment on column TB_VIDEO.scameraname
  is '����ͷ����';
comment on column TB_VIDEO.sip
  is '����ͷIP';
comment on column TB_VIDEO.svenderid
  is '���������ID';
comment on column TB_VIDEO.dgettime
  is ' ���ʱ��';
comment on column TB_VIDEO.sformat
  is '��ʽ';
comment on column TB_VIDEO.sfilesize
  is '�ļ���С';
comment on column TB_VIDEO.dstarttime
  is '��Ƶ��ʼʱ��';
comment on column TB_VIDEO.dendtime
  is '��Ƶ����ʱ��';
comment on column TB_VIDEO.spath
  is '�ļ�·��';
alter table TB_VIDEO
  add constraint VIDEO_NID primary key (NID);

prompt
prompt Creating table T_ZD_ORG
prompt =======================
prompt
create table T_ZD_ORG
(
  sorgid       VARCHAR2(30),
  sorgname     VARCHAR2(100),
  sorgnamelong VARCHAR2(200),
  sorgno       VARCHAR2(30),
  nid          NUMBER not null
)
;
comment on table T_ZD_ORG
  is '������';
comment on column T_ZD_ORG.sorgid
  is '����ID';
comment on column T_ZD_ORG.sorgname
  is '��������';
comment on column T_ZD_ORG.sorgnamelong
  is '����������';
comment on column T_ZD_ORG.sorgno
  is '������룬�����������һλ��0���ֺ����0ȫɾ��';
comment on column T_ZD_ORG.nid
  is '�ؼ���';
alter table T_ZD_ORG
  add constraint ORG_NID primary key (NID);

prompt
prompt Creating sequence SEQ_ALARM_CAR
prompt ===============================
prompt
create sequence SEQ_ALARM_CAR
minvalue 1
maxvalue 9999999999999999999999999999
start with 1
increment by 1
cache 20;

prompt
prompt Creating sequence SEQ_ALARM_VEHICLE
prompt ===================================
prompt
create sequence SEQ_ALARM_VEHICLE
minvalue 1
maxvalue 9999999999999999999999999999
start with 1
increment by 1
cache 20;

prompt
prompt Creating sequence SEQ_BLACK_CAR
prompt ===============================
prompt
create sequence SEQ_BLACK_CAR
minvalue 1
maxvalue 9999999999999999999999999999
start with 1261
increment by 1
cache 20;

prompt
prompt Creating sequence SEQ_BLACK_VEHICLE
prompt ===================================
prompt
create sequence SEQ_BLACK_VEHICLE
minvalue 1
maxvalue 9999999999999999999999999999
start with 681
increment by 1
cache 20;

prompt
prompt Creating sequence SEQ_DETECT_DEVICE
prompt ===================================
prompt
create sequence SEQ_DETECT_DEVICE
minvalue 1
maxvalue 9999999999999999999999999999
start with 140
increment by 1
cache 20;

prompt
prompt Creating sequence SEQ_LOG
prompt =========================
prompt
create sequence SEQ_LOG
minvalue 1
maxvalue 9999999999999999999999999999
start with 90320
increment by 1
cache 20;

prompt
prompt Creating sequence SEQ_MATCH_RESULT_CAR
prompt ======================================
prompt
create sequence SEQ_MATCH_RESULT_CAR
minvalue 1
maxvalue 9999999999999999999999999999
start with 14261
increment by 1
cache 20;

prompt
prompt Creating sequence SEQ_MATCH_RESULT_VEHICLE
prompt ==========================================
prompt
create sequence SEQ_MATCH_RESULT_VEHICLE
minvalue 1
maxvalue 9999999999999999999999999999
start with 91587
increment by 1
cache 20;

prompt
prompt Creating sequence SEQ_MISSION
prompt =============================
prompt
create sequence SEQ_MISSION
minvalue 1
maxvalue 9999999999999999999999999999
start with 140
increment by 1
cache 20;

prompt
prompt Creating sequence SEQ_NCAMERA
prompt =============================
prompt
create sequence SEQ_NCAMERA
minvalue 1
maxvalue 9999999999999999999999999999
start with 401
increment by 1
cache 20;

prompt
prompt Creating sequence SEQ_RECORD_PLAN
prompt =================================
prompt
create sequence SEQ_RECORD_PLAN
minvalue 1
maxvalue 9999999999999999999999999999
start with 41
increment by 1
cache 20;

prompt
prompt Creating sequence SEQ_USER
prompt ==========================
prompt
create sequence SEQ_USER
minvalue 1
maxvalue 9999999999999999999999999999
start with 141
increment by 1
cache 20;

prompt
prompt Creating sequence SEQ_VIDEO
prompt ===========================
prompt
create sequence SEQ_VIDEO
minvalue 1
maxvalue 9999999999999999999999999999
start with 325
increment by 1
cache 20;

prompt
prompt Creating sequence SEQ_ZD_ORG
prompt ============================
prompt
create sequence SEQ_ZD_ORG
minvalue 1
maxvalue 9999999999999999999999999999
start with 201
increment by 1
cache 20;

prompt
prompt Creating view DEVICELIST_VIEW
prompt =============================
prompt
create or replace view devicelist_view as
select a."NID",a."SIP",a."ISOCCUPY",a."CHANNELNUM",a."ISENABLE",a."MISSIONID",b.userid,b.isplay,to_char(b.indate) cindate,c.ncamera,c.scameraname,c.sipserver camip,c.rtspurl,c.isplay camisplay,d.suser
                 from TB_DETECT_SERVER a
                 left join tb_mission b
                 on a.missionid = b.nid
                 left join tb_device c
                 on a.nid =c.DETECTID
                  left join tb_user d
                 on d.nid = b.userid
                 order by nid desc;

prompt
prompt Creating procedure PRO_AUTO_MATCH_CAR
prompt =====================================
prompt
create or replace procedure pro_auto_match_car(i_nid        integer, --�ȶԽ����IDֵ
                                               o_cnt        out integer, --�ȶԳɹ���־��1�ɹ�0���ɹ�
                                               o_result     out integer, --ִ�н�����룬1�ɹ�0ʧ��
                                               o_errmessage out VARCHAR2 --������Ϣ��ִ�гɹ���Ϊ��
                                               ) is
  /*
    author: zzh
   created:20130327
   purpose:�Զ�ʶ�������ù�����C++����
   Logic  :�ͳ����������ȶԣ����ƺ�һ�������뱨����,���ѱ�־λ��1.
  �޸ļ�¼��
   */

begin
  o_result := 0;

  insert into tb_alarm_car
    (nid,
     SCARNUMBER,
     BPICTURE,
     DCREATE,
     SFILE,
     DGETTIME,
     NDEGREE,
     SCOLOUR,
     SDIRECTION,
     STYPE,
     sip,
     scameraname,
     nsize,
     scolor,
     ncamera,
     blackid)

    select seq_alarm_car.nextval,
           a.SCARNUMBER,
           BPICTURE,
           DCREATE,
           SFILE,
           DGETTIME,
           NDEGREE,
           SCOLOUR,
           SDIRECTION,
           STYPE,
           sip,
           scameraname,
           nsize,
           scolor,
           ncamera,
           b.nid
      from tb_match_result_car a, tb_car_black b
     where a.scarnumber = b.scarnumber
       and a.nid = i_nid;
  if sql%rowcount > 0 then
    o_cnt := 1;
  else
    o_cnt := 0;
  end if;
  --��nflag��1
  update TB_MATCH_RESULT_car set nflag = o_cnt where NID = i_NID;
  commit;
  o_result := 1;
exception
  when others then
    o_result     := 0;
    o_errmessage := sqlerrm;
    rollback;
    --������־����
end pro_auto_match_car;
/

prompt
prompt Creating procedure PRO_AUTO_MATCH_VEHICLE
prompt =========================================
prompt
create or replace procedure pro_auto_match_VEHICLE(i_nid        integer, --�ȶԽ����IDֵ
                                                   o_cnt        out integer, --�ȶԳɹ���־��1�ɹ�0���ɹ�
                                                   o_result     out integer, --ִ�н�����룬1�ɹ�0ʧ��
                                                   o_errmessage out VARCHAR2 --������Ϣ��ִ�гɹ���Ϊ��
                                                   ) is
  /*
    author: zzh
   created:20130409
   purpose:�Զ�ʶ��綯���ù�����C++����
   Logic  :�ͳ����������ȶԣ����ƺ�һ�������뱨����,���ѱ�־λ��1.
  �޸ļ�¼��
   */

begin
  o_result := 0;

  insert into tb_alarm_VEHICLE
    (nid,
     SCARNUMBER,
     BPICTURE,
     DCREATE,
     SFILE,
     DGETTIME,
     NDEGREE,
     SCOLOUR,
     SDIRECTION,
     STYPE,
     sip,
     scameraname,
     nsize,
     scolor,
     ncamera,
     blackid)

    select SEQ_ALARM_VEHICLE.Nextval,
           a.SCARNUMBER,
           BPICTURE,
           DCREATE,
           SFILE,
           DGETTIME,
           NDEGREE,
           SCOLOUR,
           SDIRECTION,
           STYPE,
           sip,
           scameraname,
           nsize,
           scolor,
           ncamera,
           b.nid
      from tb_match_result_VEHICLE a, tb_VEHICLE_black b
     where a.scarnumber = b.scarnumber
       and a.nid = i_nid;
  if sql%rowcount > 0 then
    o_cnt := 1;
  else
    o_cnt := 0;
  end if;
  --��nflag��1
  update tb_match_result_VEHICLE set nflag = o_cnt where NID = i_NID;
  commit;
  o_result := 1;
exception
  when others then
    o_result     := 0;
    o_errmessage := sqlerrm;
    rollback;
    --������־����
end pro_auto_match_VEHICLE;
/


spool off
