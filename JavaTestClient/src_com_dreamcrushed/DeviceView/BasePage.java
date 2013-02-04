package com.dreamcrushed.DeviceView;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyListener;

import javax.swing.ButtonGroup;
import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JRadioButton;
import javax.swing.JTextField;
import javax.swing.event.ChangeListener;

public class BasePage extends JPanel {
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	public int y;

	public void label(String name) {
		final JLabel label = new JLabel(name);
		label.setLocation(0, y);
		label.setSize(200, 25);
		add(label);
		y += 40;
	}

	public JButton button(String label, ActionListener listener) {
		return button(label, listener, 300, 25);
	}

	public JButton button(String label, ActionListener listener, int width, int height) {
		final JButton button = new JButton(label);
		button.addActionListener(listener);
		button.setLocation(0, y);
		button.setSize(width, height);
		add(button);
		y += height + 5;
		return button;
	}

	public JButton button(String label, ActionListener listener, int offx, int width, int height) {
		final JButton button = new JButton(label);
		button.addActionListener(listener);
		button.setLocation(offx, y);
		button.setSize(width, height);
		add(button);
		return button;
	}
	
	public JRadioButton radioField(String l, String pos, String neg, ChangeListener listener, boolean start) {
		label(l, 0, y, 200, 25);
		
		ButtonGroup group = new ButtonGroup();
		JRadioButton first = radioButton(pos, start, 0, y, 75, 25);
		group.add(first);

		group.add(radioButton(neg, !start, 75, y, 125, 25));
		
		return first;
	}

	public JTextField stringField(String l, KeyListener listener, String start) {
		label(l, 0, y, 300, 25);
		
		final JTextField display = textField(start, 0, y, 200, 25);
		display.addKeyListener(listener);
		add(display);
		
		return display;
	}
	
	public JTextField textField(String start, int x, int y, int sx, int sy) {
		final JTextField display = new JTextField(start);
		display.setLocation(x, y);
		display.setSize(sx, sy);
		this.y += sy;
		add(display);
		return display;
	}
	
	public JRadioButton radioButton(String name, boolean val, int x, int y, int sx, int sy) {
		JRadioButton jRButton = new JRadioButton(name, val);
		jRButton.setLocation(x, y);
		jRButton.setSize(sx, sy);
		add(jRButton);
		this.y += sy + 5;
		return jRButton;
	}
	
	public JLabel label(String l, int x, int y, int sx, int sy) {
		final JLabel label = new JLabel(l);
		label.setLocation(x, y);
		label.setSize(sx, sy);
		add(label);
		this.y += sy;
		return label;
	}
	
	public JCheckBox checkBox(String l, boolean state, int x, int y, int sx, int sy) {
		final JCheckBox checkBox = new JCheckBox(l, state);
		checkBox.setLocation(x, y);
		checkBox.setSize(sx, sy);
		add(checkBox);
		this.y += sy;
		return checkBox;
	}

	protected void addPreviousNext(int width) {
		JButton previous = new JButton("Previous");
		previous.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
//				DisplayManager.previous();
			}
		});
		previous.setLocation(0, y);
		previous.setSize(100, 25);
		add(previous);

		JButton next = new JButton("Next");
		next.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
//				DisplayManager.next();
			}
		});
		next.setLocation(width - 100, y);
		next.setSize(100, 25);
		add(next);
	}

}
