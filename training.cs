using System;
using System.Collections;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Windows.Forms;
using CFCNET.APPFRAME;
using CFCNET.CE;
using CFCNET.COMMAND;
using CFCNET.COMPONENT;
using CFCNET.DATA;
using CFCNET.UI;
using CFCNET.WIN32;
using RESDATA;
using WELL;
using CFCNET.APPFRAME.CONTROL;
using System.Security.Permissions;
using CFCNET.MFC;
using RESDATA2.Utilities;
using System.Runtime.InteropServices;
using System.ComponentModel;
using CFCNET.SHELL;
using CFCNET.COM;

namespace RESDATA2
{

	public interface IDataMarkLayer : ILogLayer
	{
		float this[string columnName] { get; set; }
		float this[CFCID columnID] { get; set; }
	}

	public interface IDataMarkTrace : ILogLayerTrace
	{
		IDataMarkLayer this[int index] { get; }
	}

	public class LogCurveDataMarkLayer : LogLayer, IDataMarkLayer, IArchiveSerializable, IMFCArchiveSerializable
	{
		private const int CLASS_VERSION = 0;

		public LogCurveDataMarkLayer()
			: base() {
		}
		public LogCurveDataMarkLayer(float top, float bottom)
			: base(top, bottom) {
		}
		[FormatProperty("TopDepth", typeof(double), "顶深|TopDepth")]
		[UnitText("m")]
		[DiscreteProperty]
		public float TopDepth {
			get;
			set;
		}
		[FormatProperty("BottomDepth", typeof(DipSample), "低深|BottomDepth")]
		[UnitText("")]
		public float BottomDepth {
			get;
			set;
		}
		[FormatProperty("Total_Hydrocarbon", typeof(double), "全烃|Total_Hydrocarbon")]
		[UnitText("PPM/%")]
		public float Total_Hydrocarbon {
			get;
			set;
		}
		[FormatProperty("C1", typeof(double), "甲烷|C1")]
		[UnitText("PPM/%")]
		public float C1 {
			get;
			set;
		}
		[FormatProperty("C2", typeof(double), "乙烷|C2")]
		[UnitText("PPM/%")]
		public float C2 {
			get;
			set;
		}
		[FormatProperty("C3", typeof(double), "丙烷|C3")]
		[UnitText("PPM/%")]
		public float C3 {
			get;
			set;
		}
		[FormatProperty("IC4", typeof(double), "异丁烷|IC4")]
		[UnitText("PPM/%")]
		public float IC4 {
			get;
			set;
		}
		[FormatProperty("NC4", typeof(double), "正丁烷|NC4")]
		[UnitText("PPM/%")]
		public float NC4 {
			get;
			set;
		}
		[FormatProperty("IC5", typeof(double), "异戊烷|IC5")]
		[UnitText("PPM/%")]
		public float IC5 {
			get;
			set;
		}
		[FormatProperty("NC5", typeof(double), "正戊烷| NC5")]
		[UnitText("PPM/%")]
		public float NC5 {
			get;
			set;
		}
		[FormatProperty("CO2", typeof(double), "二氧化碳|CO2")]
		[UnitText("PPM/%")]
		public float CO2 {
			get;
			set;
		}
		[FormatProperty("H2S", typeof(double), "硫化氢| H2S")]
		[UnitText("PPM/%")]
		public float H2S {
			get;
			set;
		}
		[FormatProperty("Other_Nonhydrocarbon", typeof(double), "其他非烃| Other_Nonhydrocarbon")]
		[UnitText("PPM/%")]
		public float Other_Nonhydrocarbon {
			get;
			set;
		}


		public float this[string columnName] {
			get {
				columnName = DataUtility.PackString(columnName);
				object data = this.CustomPropertyValues[columnName];
				if (data != null) {
					float v = float.NaN;
					float.TryParse(data.ToString(), out v);
					return v;
				}
				return float.NaN;
			}
			set {
				columnName = DataUtility.PackString(columnName);
				this.CustomPropertyValues[columnName] = value;
			}
		}

		public override string LayerText {
			get { return this.Name; }
		}

		public void SetLayerData(string columnName, float value) {
			this.CustomPropertyValues[columnName] = value;
		}
		public void UpDateColumnPropertys(PropertyValueCollection props) {
			foreach (PropertyValueCollection.IPropertyValue prop in props) {
				if (this.CustomPropertyValues[prop.Name] == null)
					this.CustomPropertyValues[prop.Name] = float.NaN;
			}
			int count = this.CustomPropertyValues.Count;
			int i = 0;
			while (i < count) {
				PropertyValueCollection.IPropertyValue data = this.CustomPropertyValues.GetItem(i);
				if (props[data.Name] == null) {
					this.CustomPropertyValues.Remove(data.Name);
					i--;
					count--;
				}
				i++;
			}
		}

		public void Serialize(CFCArchive ar) {
			int ver = 0;
			if (ar.IsStoring) {
				ar.Write(ver = CLASS_VERSION);
				ar.Write(this.Name);
				ar.Write(this.Top);
				ar.Write(this.Bottom);
				this.CustomPropertyValues.Serialize(ar);
			} else {
				ver = ar.ReadInt32();
				this.Name = ar.ReadString();
				this.Top = ar.ReadSingle();
				this.Bottom = ar.ReadSingle();
				this.CustomPropertyValues.Serialize(ar);
			}
		}
		public void Serialize(MFCArchive ar) {
			int ver = 0;
			if (ar.IsStoring) {
				ar.Write(ver = CLASS_VERSION);
				//ar.Write(this.Name);
				//ar.Write(this.Top);
				//ar.Write(this.Bottom);
				//this.CustomPropertyValues.Serialize(ar);
			} else {
				ver = ar.ReadInt32();
				//this.Name = ar.ReadString();
				//this.Top = ar.ReadSingle();
				//this.Bottom = ar.ReadSingle();
				//this.CustomPropertyValues.Serialize(ar);
			}
		}

		float IDataMarkLayer.this[CFCID columnID] {
			get {
				return float.NaN;
			}
			set {

			}
		}
	}

	public class LogCurveDataMarkTracePreviewHandler : LogTracePreviewHandler
	{
		#region PreviewView
		private class EditToolBar : PreviewHandlerToolBar
		{
			public readonly LogCurveDataMarkTracePreviewHandler m_handler;

			public EditToolBar(LogCurveDataMarkTracePreviewHandler handler) : base(handler) {
				this.m_handler = handler;
				base.Initialize(new object[] { SubCommandsItem.Create("文件|File", -1, new object[] { PredefCommands.FILE_SAVE, "-", PredefCommands.FILE_EXPORT, PredefCommands.FILE_IMPORT }), "-", PredefCommands.EDIT_UNDO, PredefCommands.EDIT_REDO, "-", PredefCommands.EDIT_PROPERTY_DIALOG, PredefCommands.EDIT_COPY, PredefCommands.EDIT_PASTE, "-", TableCommandEnum.InsertRow, PredefCommands.EDIT_DELETE_SELECTED_DATA, TableCommandEnum.InsertColumn });
			}

			protected override void OnGetCommandTarget(GetCommandTargetEventArgs args) {
				LogCurveDataMarkTracePreviewHandler handler = this.m_handler;
				args.CommandTarget = (handler != null) ? handler.GetView<LogCurveDataMarkTracePreviewHandler.PreviewView>() : null;
			}
		}
		private class PreviewView : LogTraceTableEditor<LogCurveDataMarkTrace>, IWin32Window, IPreviewHandlerView
		{
			#region SubItemCreatDialog
			internal class SubItemCreatDialog : XSRForm
			{
				private Button m_apply;
				private Button m_cancel;
				private LabelTextBox m_nameBox;
				private Button m_ok;
				private readonly LogCurveDataMarkTrace m_trace;
				private CommonTableColumn m_editorItem;
				private LabelComboBox m_bindTraceCombox;
				private LabelRtfControl m_titleBox;
				private LabelEnumComboBox m_readValuecombox;


				public SubItemCreatDialog(LogCurveDataMarkTrace trace, CommonTableColumn editItem) {
					if (trace == null)
						throw new Exception(XSR.TC("trace 为空。"));
					if (editItem == null)
						throw new Exception(XSR.TC("Item 为空。"));
					this.InitializeComponent();

					this.m_trace = trace;
					this.m_titleBox.Render.Text = editItem.Name;
					this.m_nameBox.Text = editItem.Name;
					//this.m_bindTraceCombox.Text = editItem.BindTraceName;
					this.m_readValuecombox.AddItems(typeof(LogTraceReadValueMethod), LogTraceReadValueMethod.Average);
					this.m_editorItem = editItem;
					this.m_bindTraceCombox.Enabled = false;
					this.m_readValuecombox.Enabled = false;
				}

				private void Apply_Click(object sender, EventArgs e) {
					try {
						this.OnApply();
					}
					catch (Exception exception) {
						ErrorMessageBox.Show(this, exception, ShowErrorOption.Message);
						ErrorMessageBox.FlushOutput();
					}
				}
				private void Cancel_Click(object sender, EventArgs e) {
					base.DialogResult = DialogResult.Cancel;
					base.Close();
				}
				private void InitializeComponent() {
					this.m_nameBox = new CFCNET.UI.LabelTextBox();
					this.m_apply = new System.Windows.Forms.Button();
					this.m_cancel = new System.Windows.Forms.Button();
					this.m_ok = new System.Windows.Forms.Button();
					this.m_bindTraceCombox = new CFCNET.UI.LabelComboBox();
					this.m_readValuecombox = new CFCNET.UI.LabelEnumComboBox();
					this.m_titleBox = new CFCNET.APPFRAME.CONTROL.LabelRtfControl();
					this.SuspendLayout();
					// 
					// m_nameBox
					// 
					this.m_nameBox.Label = "列名:";
					this.m_nameBox.LabelWidth = 40;
					this.m_nameBox.Location = new System.Drawing.Point(16, 2);
					this.m_nameBox.Name = "m_nameBox";
					this.m_nameBox.Size = new System.Drawing.Size(173, 41);
					this.m_nameBox.TabIndex = 3;
					this.m_nameBox.Toplabel = true;
					// 
					// m_apply
					// 
					this.m_apply.FlatStyle = System.Windows.Forms.FlatStyle.System;
					this.m_apply.Location = new System.Drawing.Point(125, 204);
					this.m_apply.Name = "m_apply";
					this.m_apply.Size = new System.Drawing.Size(68, 24);
					this.m_apply.TabIndex = 6;
					this.m_apply.Text = "应用";
					this.m_apply.UseVisualStyleBackColor = true;
					this.m_apply.Click += new System.EventHandler(this.Apply_Click);
					// 
					// m_cancel
					// 
					this.m_cancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
					this.m_cancel.FlatStyle = System.Windows.Forms.FlatStyle.System;
					this.m_cancel.Location = new System.Drawing.Point(269, 204);
					this.m_cancel.Name = "m_cancel";
					this.m_cancel.Size = new System.Drawing.Size(68, 24);
					this.m_cancel.TabIndex = 8;
					this.m_cancel.Text = "取消";
					this.m_cancel.Click += new System.EventHandler(this.Cancel_Click);
					// 
					// m_ok
					// 
					this.m_ok.FlatStyle = System.Windows.Forms.FlatStyle.System;
					this.m_ok.Location = new System.Drawing.Point(197, 204);
					this.m_ok.Name = "m_ok";
					this.m_ok.Size = new System.Drawing.Size(68, 24);
					this.m_ok.TabIndex = 7;
					this.m_ok.Text = "确定";
					this.m_ok.Click += new System.EventHandler(this.OK_Click);
					// 
					// m_bindTraceCombox
					// 
					this.m_bindTraceCombox.DrawMode = System.Windows.Forms.DrawMode.Normal;
					this.m_bindTraceCombox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
					this.m_bindTraceCombox.Label = "关联曲线:";
					this.m_bindTraceCombox.LabelWidth = 64;
					this.m_bindTraceCombox.Location = new System.Drawing.Point(16, 149);
					this.m_bindTraceCombox.Name = "m_bindTraceCombox";
					this.m_bindTraceCombox.Size = new System.Drawing.Size(163, 41);
					this.m_bindTraceCombox.TabIndex = 11;
					this.m_bindTraceCombox.Toplabel = true;
					// 
					// m_readValuecombox
					// 
					this.m_readValuecombox.FormattingEnabled = true;
					this.m_readValuecombox.Label = "读值方式:";
					this.m_readValuecombox.LabelWidth = 64;
					this.m_readValuecombox.Location = new System.Drawing.Point(185, 149);
					this.m_readValuecombox.Name = "m_readValuecombox";
					this.m_readValuecombox.Size = new System.Drawing.Size(150, 41);
					this.m_readValuecombox.TabIndex = 12;
					this.m_readValuecombox.Toplabel = true;
					// 
					// m_titleBox
					// 
					this.m_titleBox.Label = "标题:";
					this.m_titleBox.Location = new System.Drawing.Point(16, 46);
					this.m_titleBox.Multiline = true;
					this.m_titleBox.Name = "m_titleBox";
					this.m_titleBox.Size = new System.Drawing.Size(319, 93);
					this.m_titleBox.TabIndex = 13;
					this.m_titleBox.Toplabel = true;
					// 
					// SubItemCreatDialog
					// 
					this.AcceptButton = this.m_ok;
					this.CancelButton = this.m_cancel;
					this.ClientSize = new System.Drawing.Size(349, 238);
					this.Controls.Add(this.m_titleBox);
					this.Controls.Add(this.m_readValuecombox);
					this.Controls.Add(this.m_bindTraceCombox);
					this.Controls.Add(this.m_apply);
					this.Controls.Add(this.m_cancel);
					this.Controls.Add(this.m_ok);
					this.Controls.Add(this.m_nameBox);
					this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
					this.MaximizeBox = false;
					this.MinimizeBox = false;
					this.Name = "SubItemCreatDialog";
					this.ShowIcon = false;
					this.ShowInTaskbar = false;
					this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
					this.ResumeLayout(false);

				}
				private void OK_Click(object sender, EventArgs e) {
					try {
						this.OnApply();
						base.DialogResult = DialogResult.OK;
						base.Close();
					}
					catch (Exception exception) {
						ErrorMessageBox.Show(this, exception, ShowErrorOption.Message);
						ErrorMessageBox.FlushOutput();
					}
				}
				private void OnApply() {
					this.m_editorItem.Title = this.m_nameBox.Text;
				}
			}
			#endregion

			private LogCurveDataMarkTrace m_trace;
			private XShellPreviewOptions m_options;
			public readonly LogCurveDataMarkTracePreviewHandler m_handler;

			public PreviewView(LogCurveDataMarkTracePreviewHandler handler) {
				if (handler == null) {
					throw new ArgumentNullException("handler");
				}
				this.m_handler = handler;
				this.Options = handler.Options;
				base.ReadOnly = !this.SupportEdit;
				this.ReloadData();
			}

			public bool ExplorerEmbed {
				get {
					return ((this.Options & XShellPreviewOptions.ExplorerEmbed) != XShellPreviewOptions.Default);
				}
			}
			public bool SupportEdit {
				get {
					return ((this.Options & XShellPreviewOptions.SupportEdit) != XShellPreviewOptions.Default);
				}
			}
			public Margin LayoutMargin {
				get {
					if (!this.ExplorerEmbed) {
						return new Margin(0);
					}
					return new Margin(0, 0, 2, 0);
				}
			}
			public XShellPreviewOptions Options {
				get {
					return this.m_options;
				}
				private set {
					this.m_options = value;
				}
			}

			public override bool HaveData {
				get {
					return (this.m_trace != null);
				}
			}
			public override LogCurveDataMarkTrace Trace {
				get {
					return this.m_trace;
				}
				set {
					if (this.m_trace != value) {
						this.Clear();
						if (value != null) {
							ComponentTableColumnCollection implColumns = base.ImplColumns;
							implColumns.AddRange(ParsePropertyCollection.GetProperties(value.LayerType));
							int count = implColumns.Count;
							if (value is ILogTraceAttributeSupport) {
								implColumns.AddRange(((ILogTraceAttributeSupport)value).GetElementExtendProperties());
							}
							int num = count;
							int num3 = implColumns.Count;
							while (num < num3) {
								UIPropertyDescriptor descriptor = implColumns[num];
								descriptor.CanXTRDesign = false;
								num++;
							}
							this.m_trace = DataUtility.Clone<LogCurveDataMarkTrace>(value);
							this.m_trace.ChangedNotifier = this;
							base.Data = this.m_trace.Layers;
							base.ResetUndoService();
							base.Modified = false;
						}
					}
				}
			}
			public override string TraceName {
				get {
					LogLayerTraceBase base2 = this.m_trace;
					if (base2 == null) {
						return string.Empty;
					}
					return base2.Name;
				}
			}
			protected override bool OwnerUndoService {
				get {
					return this.SupportEdit;
				}
			}

			public void OnHandlerClosing(CancelEventArgs args) {
				if ((this.SupportEdit && base.Modified) && this.HaveData) {
					string text = XSR.SplitSelect("是否保存对文档的更改？|The document has been modified. Do you neet to save it ?");
					switch (MessageBox.Show(this, text, Application.ProductName, MessageBoxButtons.YesNoCancel)) {
					case DialogResult.Cancel:
						args.Cancel = true;
						break;

					case DialogResult.Yes:
						this.SaveTrace();
						break;
					}
				}
				if (!args.Cancel) {
					base.ResetUndoService();
				}
			}
			public void ReloadData() {
				base.LoadData(this.m_handler.Data);
				LogCurveDataMarkTrace trace = this.m_handler.Data as LogCurveDataMarkTrace;
				if (trace != null) {
					trace.LayerCustomProperties.Clear();
					ValueProperty[] ps = PropertyValueCollection.PickProperties(new PropertyValueCollection[] { trace.CustomPropertyValues });
					foreach (ValueProperty property in ps) {
						trace.LayerCustomProperties.Add(property.Name, property.PropertyType);
					}
					base.ImplColumns.AddRange(ps);
				}
			}
			protected override WellName OnGetWellName() {
				LogCurveDataMarkTracePreviewHandler handler = this.m_handler;
				if (handler != null) {
					return handler.WellName;
				}
				return base.OnGetWellName();
			}
			private void Clear() {
				base.ResetTable();
				LogLayerTraceBase base2 = this.m_trace;
				if (base2 != null) {
					this.m_trace = null;
					base2.ChangedNotifier = null;
				}
			}
			private void EditLayer(int rowIndex) {
				LogCurveDataMarkLayer layer = this.m_trace.Layers[rowIndex] as LogCurveDataMarkLayer;
				using (LogCurveDataMarkTrace.LogCurveDataMarkLayerPropertyDlg dlg = new LogCurveDataMarkTrace.LogCurveDataMarkLayerPropertyDlg(layer, this.m_trace)) {
					if (dlg.ShowDialog(this.GetDialogOwner()) == DialogResult.OK) {
						this.m_trace.Layers.Add(layer);
					}
				}
			}
			private void InsertLayer() {
				LogCurveDataMarkLayer layer = new LogCurveDataMarkLayer();
				using (LogCurveDataMarkTrace.LogCurveDataMarkLayerPropertyDlg dlg = new LogCurveDataMarkTrace.LogCurveDataMarkLayerPropertyDlg(layer, this.m_trace)) {
					dlg.ShowDialog(this.GetDialogOwner());
				}
			}
			private void InsertColumn() {
				CommonTableColumn column = new CommonTableColumn(typeof(string), "列1", 50);
				using (SubItemCreatDialog dlg = new SubItemCreatDialog(this.m_trace, column)) {
					dlg.Text = "新建列";
					if (dlg.ShowDialog(this.GetDialogOwner()) == DialogResult.OK) {
						LogCurveDataMarkTrace trace = this.m_handler.Data as LogCurveDataMarkTrace;
						trace.CustomPropertyValues[column.Title] = column.Title;
					}
				}
				this.ReloadData();
			}

			private void SaveTrace() {
				LogCurveDataMarkTracePreviewHandler handler = this.m_handler;
				try {
					LogCurveDataMarkTrace data = (handler != null) ? this.Trace : null;
					if (data != null) {
						handler.SaveLogTrace(data);
						base.Modified = false;
					}
				}
				catch (Exception exception) {
					ErrorMessageBox.Show(this, exception, ShowErrorOption.Message);
					ErrorMessageBox.FlushOutput();
				}
			}
			protected override void OnBuildMenu(TableBuildMenuEventArgs e) {
				base.OnBuildMenu(e);
			}
			[Command(TableCommandEnum.InsertColumn)]
			private void Command_AddColumn(CommandArgs e) {
				bool flag = (this.m_trace != null) && !base.ReadOnly;
				if (e.IsUpdate) {
					e.Command.Enabled = flag;
				} else if (flag) {
					this.InsertColumn();
				}
			}
			[Command(TableCommandEnum.InsertRow)]
			private void Command_AddLayer(CommandArgs e) {
				bool flag = (this.m_trace != null) && !base.ReadOnly;
				if (e.IsUpdate) {
					e.Command.Enabled = flag;
				} else if (flag) {
					this.InsertLayer();
				}
			}
			[Command(PredefCommands.EDIT_COPY)]
			private void Command_Copy(CommandArgs e) {
				LogLayerTraceBase base2 = this.m_trace;
				bool flag = base2 != null;
				if (e.IsUpdate) {
					e.Command.Enabled = flag;
				} else if (flag) {
					bool entireDepthRange = true;
					float top = base2.Top;
					float bottom = base2.Bottom;
					LogLayer[] selectedRowComponents = base.ImplRows.GetSelectedRowComponents<LogLayer>();
					if (selectedRowComponents.Length > 0) {
						float maxValue = float.MaxValue;
						float minValue = float.MinValue;
						foreach (LogLayer layer in selectedRowComponents) {
							maxValue = Math.Min(layer.Top, maxValue);
							minValue = Math.Max(layer.Bottom, minValue);
						}
						if (maxValue < minValue) {
							top = maxValue;
							bottom = minValue;
							entireDepthRange = false;
						}
					}
					try {
						using (SelectCopyDataRangeDialog dialog = new SelectCopyDataRangeDialog(top, bottom, entireDepthRange)) {
							if (dialog.ShowDialog(this) == DialogResult.OK) {
								DepthZone zone = dialog.Zone;
								LogLayerTraceBase base3 = (LogLayerTraceBase)base2.Copy(zone.Top, zone.Bottom);
								base3.Name = base2.Name;
								LogTraceSet set = new LogTraceSet(new LogTrace[] { base3 });
								set.WellName = base.WellName.Name;
								LogTraceCopyOptions options = LogTraceCopyOptions.None;
								if (dialog.CopyASCII) {
									options |= LogTraceCopyOptions.Text;
								}
								if (dialog.CopyInternal) {
									options |= LogTraceCopyOptions.Binary;
								}
								set.CopyToClipboard(options);
							}
						}
					}
					catch (Exception exception) {
						base.ShowErrorMessage(exception);
					}
				}
			}
			[Command(PredefCommands.EDIT_PROPERTY_DIALOG)]
			private void Command_EditLayer(CommandArgs e) {
				LogLayerTraceBase base2 = this.m_trace;
				bool flag = (((base2 != null) && base2.CanEditLayer) && (base.ImplRows.Count > 0)) && base.Selections.IsRowSelection;
				if (e.IsUpdate) {
					e.Command.Enabled = flag;
				} else if (flag) {
					int top = base.Selections[0].Range.Top;
					this.EditLayer(top);
				}
			}
			[Command(PredefCommands.FILE_IMPORT)]
			private void Command_Import(CommandArgs e) {
				LogLayerTraceBase base2 = this.m_trace;
				bool flag = (base2 != null) && !base.ReadOnly;
				if (e.IsUpdate) {
					e.Command.Enabled = flag;
				} else if (flag) {
					try {
						ImportLogTraceParams traceParams = new ImportLogTraceParams(new Type[] { base2.GetType() }, base.WellName, new string[] { base2.Name });
						LogLayerTraceBase base3 = (LogLayerTraceBase)ResDataUtility.ImportFromFile_Trace(traceParams);
						if (base3 != null) {
							ComponentTableRow.Collection implRows = base.ImplRows;
							if (implRows.Count > 0) {
								using (AddOrReplaceDataDialog dialog = new AddOrReplaceDataDialog()) {
									if (dialog.ShowDialog(this) == DialogResult.OK) {
										LogLayerTraceBase base4 = DataUtility.Clone<LogLayerTraceBase>(base2);
										if (dialog.ReplaceData) {
											base4.Layers.Load(base3.Layers, LogTraceLoadMode.Overlay, UpdateDataDepthZone.MaxRange);
										} else {
											base4.Layers.Load(base3.Layers, LogTraceLoadMode.Merge, UpdateDataDepthZone.MaxRange);
										}
										implRows.Replace(base4.Layers.ToArray(UpdateDataDepthZone.MaxRange, true));
									}
									return;
								}
							}
							implRows.Replace(base3.Layers.ToArray(UpdateDataDepthZone.MaxRange, true));
						}
					}
					catch (Exception exception) {
						base.ShowErrorMessage(exception);
					}
				}
			}
			[Command(PredefCommands.EDIT_PASTE)]
			private void Command_Paste(CommandArgs e) {
				LogLayerTraceBase base2 = this.m_trace;
				bool flag = ((base2 != null) && !base.ReadOnly) && ResDataUtility.CanPasteLogTrace(true);
				if (e.IsUpdate) {
					e.Command.Enabled = flag;
				} else if (flag) {
					try {
						ImportLogTraceParams traceParams = new ImportLogTraceParams(new Type[] { base2.GetType() }, base.WellName, new string[] { base2.Name });
						LogLayerTraceBase base3 = (LogLayerTraceBase)ResDataUtility.ImportFromClipbord_Trace(traceParams);
						if (base3 != null) {
							ComponentTableRow.Collection implRows = base.ImplRows;
							if (implRows.Count > 0) {
								using (AddOrReplaceDataDialog dialog = new AddOrReplaceDataDialog()) {
									if (dialog.ShowDialog(this) == DialogResult.OK) {
										LogLayerTraceBase base4 = DataUtility.Clone<LogLayerTraceBase>(base2);
										if (dialog.ReplaceData) {
											base4.Layers.Load(base3.Layers, LogTraceLoadMode.Overlay, UpdateDataDepthZone.MaxRange);
										} else {
											base4.Layers.Load(base3.Layers, LogTraceLoadMode.Merge, UpdateDataDepthZone.MaxRange);
										}
										implRows.Replace(base4.Layers.ToArray(UpdateDataDepthZone.MaxRange, true));
									}
									return;
								}
							}
							implRows.Replace(base3.Layers.ToArray(UpdateDataDepthZone.MaxRange, true));
						}
					}
					catch (Exception exception) {
						base.ShowErrorMessage(exception);
					}
				}
			}
			[Command(TableCommandEnum.RemoveSelectedRows)]
			private void Command_RemoveSelectedLayers(CommandArgs e) {
				bool flag = base.CanRemoveSelectedRows();
				if (e.IsUpdate) {
					e.Command.Enabled = flag;
				} else if (flag) {
					UndoItem item = new UndoItem();
					try {
						this.Rows.RemoveSelected(true, item);
						base.PushUndo(item);
					}
					catch (Exception exception) {
						base.DoUndo(item);
						base.ShowErrorMessage(exception);
					}
				}
			}
			[Command(PredefCommands.FILE_SAVE)]
			private void Command_Save(CommandArgs e) {
				bool flag = this.HaveData && this.m_handler.CanSave;
				if (e.IsUpdate) {
					e.Command.Enabled = flag;
				} else if (flag) {
					this.SaveTrace();
				}
			}
		}
		#endregion

		public LogCurveDataMarkTracePreviewHandler() {

		}
		public void SaveLogTrace(LogCurveDataMarkTrace trace) {
			base.Save(trace);
		}
		protected override void OnClosing(SaveFileCancelEventArgs e) {
			PreviewView view = base.GetView<PreviewView>();
			if (view != null) {
				view.OnHandlerClosing(e);
			}
		}
		protected override Control OnCreateToolBar() {
			return new EditToolBar(this);
		}
		protected override Control OnCreateView(BorderStyle border) {
			return new PreviewView(this);
		}
		protected override bool ToolBarVisible {
			get {
				return ((base.Options & XShellPreviewOptions.SupportEdit) != XShellPreviewOptions.Default);
			}
		}
	}
	[PreviewHandlerType(typeof(LogCurveDataMarkTracePreviewHandler))]
	[ShowOrder(21), IconIndex(416), DefaultTraceName("曲线深度段标注", "CurveDataMark"), Caption("曲线深度段标注道", "CurveDataMarkTrace"), RegisterClass("FE67F83B-3E4A-4411-BF9A-A50951835D93", "RESDATA2.LogGasInterpretationTrace", Name = "曲线深度段标注道"), LogLayerType(typeof(LogCurveDataMarkLayer))]
	public class LogCurveDataMarkTrace : LogLayerTraceBase, IDataMarkTrace
	{
		#region TextParsePage
		[LogTraceExchanger_TextAndExcelFiles(typeof(LogCurveDataMarkTrace))]
		public class TextParsePageA : LogLayerTraceBase.TextParsePageBase
		{
		}
		#endregion
		#region TextParsePage
		[LogTraceExchanger(typeof(LogCurveDataMarkTrace), "文本文件 (*.txt)|*.txt|Excel文件 (*.xls;*.xlsx)|*.xls;*.xlsx|所有文件 (*.*)|*.*", Description = "行文本、Excel")]
		public class TextParsePage : LogLayerTraceBase.TextParsePageBase
		{
			private string[] m_traceNames;

			public TextParsePage() {
			}

			protected override void OnAutoMatchColumns() {
				string[] columns;
				string[][] data = base.DataControl.Data;
				if (data != null && data.Length > 0 && (columns = data[0]) != null) {
					this.MatchColumns(columns, 0, true, false);
				}
			}
			protected override void OnMatchColumns(string[] line, int lineIndex) {
				this.MatchColumns(line, lineIndex, true, true);
			}
			protected override void OnParseText(DataColumnAssigner dataCtrl, int startLine, string[][] data, FieldExchangeSource buffer) {
				List<string> additionColumns = new List<string>(dataCtrl.ColumnNames);

				int topDepthColumnIndex = dataCtrl.GetColumnIndex(LogTraceTextParsePage.PropTopDepth.Name);
				if (topDepthColumnIndex < 0) {
					throw new Exception(XSR.TC("没有指定“顶深”列。"));
				}
				additionColumns.Remove(LogTraceTextParsePage.PropTopDepth.Name);
				int bottomDepthColumnIndex = dataCtrl.GetColumnIndex(LogTraceTextParsePage.PropBottomDepth.Name);
				if (bottomDepthColumnIndex < 0) {
					throw new Exception(XSR.TC("没有指定“底深”列。"));
				}
				additionColumns.Remove(LogTraceTextParsePage.PropBottomDepth.Name);
				int wellNameColumnIndex = dataCtrl.GetColumnIndex(LogTraceTextParsePage.PropWellName.Name);
				if (wellNameColumnIndex >= 0)
					additionColumns.Remove(LogTraceTextParsePage.PropWellName.Name);
				int layerNameColumnIndex = dataCtrl.GetColumnIndex(LogTraceTextParsePage.PropLayerName.Name);
				if (layerNameColumnIndex >= 0)
					additionColumns.Remove(LogTraceTextParsePage.PropLayerName.Name);

				LogCurveDataMarkTrace trace = new LogCurveDataMarkTrace();
				trace.Name = XSR.TC("曲线深度段标注");
				trace.IntizeColumns(additionColumns.ToArray());
				int readline = startLine;
				while (readline < data.Length) {
					base.SetCurrentParseLine(readline);
					if (dataCtrl.IsRowUsed(readline)) {
						try {
							string[] strArray = data[readline];
							double top = base.ParseDepth(strArray[topDepthColumnIndex]);
							double bottom = base.ParseDepth(strArray[bottomDepthColumnIndex]);
							if (!double.IsNaN(top) && (top >= 0.0) && !double.IsNaN(bottom) && (bottom > top)) {
								LogCurveDataMarkLayer layer = new LogCurveDataMarkLayer((float)top, (float)bottom);
								if (layerNameColumnIndex >= 0) {
									string layerName = strArray[layerNameColumnIndex];
									layer.Name = layerName;
								}
								foreach (string columnName in additionColumns) {
									float columnValue = float.NaN;
									int columnIndex = dataCtrl.GetColumnIndex(columnName);
									if (columnIndex >= 0) {
										float.TryParse(strArray[columnIndex], out columnValue);
									}
									layer.SetLayerData(columnName, columnValue);
								}
								trace.AddLayer(layer, AddLayerFailActions.Cancel);
							}
						}
						catch {
						}
					}
					readline++;
				}
				buffer.Wells[LogTraceTextParsePage.PropWellName.Name].Traces.AddItem(trace, true);
			}
			private void MatchColumns(string[] line, int lineIndex, bool pickTraceNames, bool showPickTraceNamesDialog) {
				if (line == null) {
					line = new string[0];
				}
				if (pickTraceNames) {
					Hashtable mustPropertys = new CaseInsensitiveHashtable();
					LogTraceTextParsePage.PropWellName.SetAliasDictionary(mustPropertys);
					List<string> propertyNames = new List<string>();
					foreach (ParseProperty property in this.Properties) {
						property.SetAliasDictionary(mustPropertys);
						propertyNames.Add(property.Name);
					}
					List<string> additionColumn = new List<string>();
					foreach (string text in line) {
						string key = ResDataUtility.NormalizeLogTraceName(LogTraceTextParsePage.PackTitle(text));
						if (((key.Length > 0) && !mustPropertys.Contains(key)) && StringHaveLetter(key)) {
							if (key.Equals(XSR.TC("层厚")))//ResForm软件导出文本附加列，如果不过滤掉把该列加入数据中，复制、导出数据时会有重复列报错
								continue;
							additionColumn.Add(key);
						}
					}
					this.m_traceNames = new string[mustPropertys.Values.Count];
					mustPropertys.Keys.CopyTo(this.m_traceNames, 0);
					string[] matchedColumn = this.MatchGo(line, additionColumn.ToArray(), propertyNames.ToArray(), this.m_traceNames, showPickTraceNamesDialog);
					base.DataControl.SetColumnSelectNames(matchedColumn);
					base.SetStartLine(lineIndex + 1);
					base.UpdateStates();
				}

			}
			private string[] MatchGo(string[] line, string[] additionColumns, string[] mustColumns, string[] columnBindAttrubiteName, bool showPickTraceNamesDialog) {
				List<string> matchedColumn = new List<string>();
				if (!showPickTraceNamesDialog) {
					matchedColumn.AddRange(mustColumns);
					foreach (string column in additionColumns) {
						string regularText = ResDataUtility.NormalizeLogTraceName(column);
						matchedColumn.Add(regularText);
					}
					base.DataControl.ColumnNames = matchedColumn.ToArray();
					foreach (string text in line) {
						string regularText = ResDataUtility.NormalizeLogTraceName(text);
						if (matchedColumn.Contains(regularText)) {
							matchedColumn.Add(regularText);
							matchedColumn.Remove(regularText);
						} else
							matchedColumn.Add(string.Empty);
					}
				} else {
					using (PickColumnNamesDialog dialog = new PickColumnNamesDialog(additionColumns, false, new PickColumnNamesDialog.NamePacker(ResDataUtility.NormalizeLogTraceName))) {
						dialog.SetAllItemsCheckState(true);
						if (base.IsPaste) {
							dialog.Text = XSR.TC("选择要粘贴的道名");
						} else {
							dialog.Text = XSR.TC("选择要加载的道名");
						}
						if (dialog.ShowDialog(base.Dialog) == DialogResult.OK) {
							additionColumns = dialog.SelectedNames;
						}
						List<string> finalColumns = new List<string>(mustColumns);
						finalColumns.AddRange(additionColumns);
						base.DataControl.ColumnNames = finalColumns.ToArray();

						finalColumns = new List<string>(columnBindAttrubiteName);
						finalColumns.AddRange(additionColumns);

						foreach (string text in line) {
							string regularText = ResDataUtility.NormalizeLogTraceName(text);
							if (finalColumns.Contains(regularText)) {
								matchedColumn.Add(regularText);
								finalColumns.Remove(regularText);
							} else
								matchedColumn.Add(string.Empty);
						}
					}
				}
				return matchedColumn.ToArray();
			}
			private static bool StringHaveLetter(string str) {
				foreach (char ch in str) {
					if (char.IsLetter(ch)) {
						return true;
					}
				}
				return false;
			}

		}
		#endregion
		#region EditDialog
		internal class LogCurveDataMarkLayerPropertyDlg : Form
		{
			private ComponentPropertyGrid m_gridView;
			private System.Windows.Forms.Button m_ok;
			private System.Windows.Forms.Button m_cancel;
			private LabelTextBox m_layerName;
			private System.Windows.Forms.GroupBox m_depthGroup;
			private RESDATA.LabelDepthBox m_topD;
			private RESDATA.LabelDepthBox m_bottomD;

			private LogCurveDataMarkLayer m_editlayer;
			private readonly LogCurveDataMarkLayer m_layer;
			private readonly LogCurveDataMarkTrace m_trace;

			public LogCurveDataMarkLayerPropertyDlg(LogCurveDataMarkLayer layer, LogCurveDataMarkTrace ownerTrace) {
				InitializeComponent();
				this.m_layer = layer;
				this.m_editlayer = layer.Clone() as LogCurveDataMarkLayer;
				this.m_trace = ownerTrace;
				this.m_topD.Text = this.m_editlayer.Top.ToString();
				this.m_bottomD.Text = this.m_editlayer.Bottom.ToString();
				this.m_layerName.Text = this.m_editlayer.Name;

				ValueProperty[] ps = PropertyValueCollection.PickProperties(new PropertyValueCollection[] { this.m_trace.CustomPropertyValues });
				this.m_gridView.Properties.AddRange(ps);
				this.m_gridView.Component = m_editlayer;
			}

			private void InitializeComponent() {
				this.m_gridView = new CFCNET.APPFRAME.CONTROL.ComponentPropertyGrid();
				this.m_ok = new System.Windows.Forms.Button();
				this.m_cancel = new System.Windows.Forms.Button();
				this.m_layerName = new CFCNET.UI.LabelTextBox();
				this.m_depthGroup = new System.Windows.Forms.GroupBox();
				this.m_topD = new RESDATA.LabelDepthBox();
				this.m_bottomD = new RESDATA.LabelDepthBox();
				this.m_depthGroup.SuspendLayout();
				this.SuspendLayout();
				// 
				// m_gridView
				// 
				this.m_gridView.Location = new System.Drawing.Point(10, 21);
				this.m_gridView.Name = "m_gridView";
				this.m_gridView.Size = new System.Drawing.Size(308, 208);
				this.m_gridView.TabIndex = 0;
				// 
				// m_ok
				// 
				this.m_ok.FlatStyle = System.Windows.Forms.FlatStyle.System;
				this.m_ok.Location = new System.Drawing.Point(200, 346);
				this.m_ok.Name = "m_ok";
				this.m_ok.Size = new System.Drawing.Size(68, 24);
				this.m_ok.TabIndex = 8;
				this.m_ok.Text = "确定";
				this.m_ok.Click += new System.EventHandler(this.button_ok_Click);
				// 
				// m_cancel
				// 
				this.m_cancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
				this.m_cancel.FlatStyle = System.Windows.Forms.FlatStyle.System;
				this.m_cancel.Location = new System.Drawing.Point(271, 346);
				this.m_cancel.Name = "m_cancel";
				this.m_cancel.Size = new System.Drawing.Size(68, 24);
				this.m_cancel.TabIndex = 9;
				this.m_cancel.Text = "取消";
				this.m_cancel.Click += new System.EventHandler(this.button_cancel_Click);
				// 
				// m_layerName
				// 
				this.m_layerName.Label = "层号:";
				this.m_layerName.LabelWidth = 40;
				this.m_layerName.Location = new System.Drawing.Point(25, 14);
				this.m_layerName.Name = "m_layerName";
				this.m_layerName.Size = new System.Drawing.Size(311, 23);
				this.m_layerName.TabIndex = 10;
				// 
				// m_depthGroup
				// 
				this.m_depthGroup.Controls.Add(this.m_gridView);
				this.m_depthGroup.FlatStyle = System.Windows.Forms.FlatStyle.System;
				this.m_depthGroup.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
				this.m_depthGroup.Location = new System.Drawing.Point(12, 99);
				this.m_depthGroup.Name = "m_depthGroup";
				this.m_depthGroup.Size = new System.Drawing.Size(324, 241);
				this.m_depthGroup.TabIndex = 11;
				this.m_depthGroup.TabStop = false;
				this.m_depthGroup.Text = "标注属性";
				// 
				// m_topD
				// 
				this.m_topD.Label = "顶深:";
				this.m_topD.Location = new System.Drawing.Point(25, 49);
				this.m_topD.Name = "m_topD";
				this.m_topD.Size = new System.Drawing.Size(140, 41);
				this.m_topD.TabIndex = 0;
				this.m_topD.Toplabel = true;
				// 
				// m_bottomD
				// 
				this.m_bottomD.Label = "底深:";
				this.m_bottomD.Location = new System.Drawing.Point(196, 49);
				this.m_bottomD.Name = "m_bottomD";
				this.m_bottomD.Size = new System.Drawing.Size(140, 41);
				this.m_bottomD.TabIndex = 1;
				this.m_bottomD.Toplabel = true;
				// 
				// WellCurveDataMarkLayerPropertyDlg
				// 
				this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
				this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
				this.ClientSize = new System.Drawing.Size(351, 378);
				this.Controls.Add(this.m_topD);
				this.Controls.Add(this.m_layerName);
				this.Controls.Add(this.m_bottomD);
				this.Controls.Add(this.m_depthGroup);
				this.Controls.Add(this.m_ok);
				this.Controls.Add(this.m_cancel);
				this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
				this.MaximizeBox = false;
				this.MinimizeBox = false;
				this.Name = "WellCurveDataMarkLayerPropertyDlg";
				this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
				this.Text = "曲线标注层";
				this.m_depthGroup.ResumeLayout(false);
				this.ResumeLayout(false);

			}
			private void button_ok_Click(object sender, EventArgs e) {
				try {
					this.OnApply();
					base.DialogResult = DialogResult.OK;
					base.Close();
				}
				catch (Exception exception) {
					MessageBox.Show(this, CFCException.GetMessage(exception), Application.ProductName);
				}
			}
			private void button_cancel_Click(object sender, EventArgs e) {
				base.DialogResult = DialogResult.Cancel;
				base.Close();
			}
			private void OnApply() {
				float top = this.m_topD.Value;
				float bottom = this.m_bottomD.Value;
				if (top >= bottom) {
					throw new Exception(XSR.TC("顶深不能大于底深！"));
				}
				this.m_editlayer.Top = top;
				this.m_editlayer.Bottom = bottom;
				this.m_editlayer.Name = this.m_layerName.Text;
				this.m_layer.Update(this.m_editlayer);
			}
		}
		#endregion

		private const int CLASS_VERSION = 0;

		public LogCurveDataMarkTrace()
			: base() {
		}

		public IDataMarkLayer this[int index] {
			get {
				LogLayer layer = this.GetAt(index);
				if (layer != null)
					return layer as IDataMarkLayer;
				return null;
			}
		}
		public override bool CanEditLayer {
			get {
				return true;
			}
		}
		public override DialogResult EditLayer(LogLayer layer, IWin32Window winOwner, bool readOnly) {
			DialogResult r = DialogResult.No;
			using (LogCurveDataMarkLayerPropertyDlg dlg = new LogCurveDataMarkLayerPropertyDlg((LogCurveDataMarkLayer)layer, this)) {
				r = dlg.ShowDialog(winOwner);
			}
			return r;
		}
		public void IntizeColumns(string[] columnNames) {
			if (columnNames == null)
				return;
			foreach (string columnName in columnNames) {
				this.CustomPropertyValues[columnName] = columnName;
			}
			this.FlushAllLayer();
		}
		public void AddColumn(string columnName) {
			this.CustomPropertyValues[columnName] = columnName;
			this.FlushAllLayer();
		}
		public void RemoveColumn(string columnName) {
			this.CustomPropertyValues.Remove(columnName);
			this.FlushAllLayer();
		}
		public void FlushAllLayer() {
			foreach (LogCurveDataMarkLayer layer in this.Layers) {
				if (layer != null)
					layer.UpDateColumnPropertys(this.CustomPropertyValues);
			}
		}

		protected override void OnLayerAdded(LogLayerEventArgs e) {
			base.OnLayerAdded(e);
			//LogCurveDataMarkLayer layer = e.Layer as LogCurveDataMarkLayer;
			//for (int i = 0; i < this.CustomPropertyValues.Count; i++) {
			//    PropertyValueCollection.IPropertyValue property = this.CustomPropertyValues.GetItem(i);
			//    if (property != null)
			//        layer.SetLayerData(property.Name, float.NaN);
			//}
		}
		protected override void OnSerialize(MFCArchive ar) {
			int ver, count;
			if (ar.IsStoring) {
				ar.Write(ver = CLASS_VERSION);
				//this.CustomPropertyValues.Serialize(ar);
				ar.Write(count = this.Count);
				LogLayer.Collection layers = this.Layers;
				for (int i = 0; i < count; i++) {
					LogCurveDataMarkLayer layer = layers[i] as LogCurveDataMarkLayer;
					if (layer != null) {
						layer.Serialize(ar);
					}
				}
			} else {
				ver = ar.ReadInt32();
				//this.CustomPropertyValues.Serialize(ar);
				count = ar.ReadInt32();
				LogLayer.Collection layers = base.Layers;
				layers.Clear();
				for (int i = 0; i < count; i++) {
					LogCurveDataMarkLayer layer = new LogCurveDataMarkLayer();
					if (layer != null) {
						layer.Serialize(ar);
						layers.Add(layer);
					}
				}
			}
		}
		protected override void OnSerialize(CFCArchive ar, int version) {
			int ver, count;
			if (ar.IsStoring) {
				ar.Write(ver = CLASS_VERSION);
				this.CustomPropertyValues.Serialize(ar);
				ar.Write(count = this.Count);
				LogLayer.Collection layers = this.Layers;
				for (int i = 0; i < count; i++) {
					LogCurveDataMarkLayer layer = layers[i] as LogCurveDataMarkLayer;
					if (layer != null) {
						layer.Serialize(ar);
					}
				}
			} else {
				ver = ar.ReadInt32();
				this.CustomPropertyValues.Serialize(ar);
				count = ar.ReadInt32();
				LogLayer.Collection layers = base.Layers;
				layers.Clear();
				for (int i = 0; i < count; i++) {
					LogCurveDataMarkLayer layer = new LogCurveDataMarkLayer();
					if (layer != null) {
						layer.Serialize(ar);
						layers.Add(layer);
					}
				}
			}
		}
		//protected override DialogResult OnBrowse(string wellName, PropertyDefineCollectionManager customPropertyManager)
		//{
		//    DialogResult r = DialogResult.No;
		//    this.LayerCustomProperties.Clear();
		//    ValueProperty[] ps = PropertyValueCollection.PickProperties(new PropertyValueCollection[] { this.CustomPropertyValues });
		//    foreach (ValueProperty property in ps)
		//    {
		//        this.LayerCustomProperties.Add(property.Name, property.PropertyType);
		//    }
		//    using (LogLayerTraceBrowser br = new LogLayerTraceBrowser(this, wellName, customPropertyManager))
		//    {
		//        ((ILogTraceBrowser)br).Editor.Columns.AddRange(ps);
		//        r = br.ShowDialog(this.GetBrowserOwner());
		//    }
		//    return r;
		//}

	}

}
